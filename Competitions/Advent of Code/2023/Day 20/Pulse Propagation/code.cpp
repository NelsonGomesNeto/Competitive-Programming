#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

const int kButtonPushes = 1e3;

enum Type { STANDARD, FLIP_FLOP, CONJUCTION, BROADCASTER };
const std::vector<std::string> kTypeName = {"STANDARD", "FLIP_FLOP",
                                            "CONJUCTION", "BROADCASTER"};
Type GetType(char t) {
  if (t == '%') return Type::FLIP_FLOP;
  if (t == '&') return Type::CONJUCTION;
  return Type::STANDARD;
}
enum Pulse { LOW, HIGH };
const std::vector<std::string> kPulseName = {"LOW", "HIGH"};

const std::string kBroadcasterName = "broadcaster";
const std::string kButtonName = "button";

struct Module;

struct Message {
  Module& from;
  Module& to;
  Pulse pulse;
  int timestamp;
  int to_index;
};

struct Module {
  std::string name;
  Type type = Type::STANDARD;
  std::vector<std::shared_ptr<Module>> destinations;
  std::vector<int> index_on_destination_input;

  bool on = false;
  std::vector<Pulse> input_pulse_history;

  Module() {}
  Module(const std::string name) : name(name) {}

  friend std::ostream& operator<<(std::ostream& stream, const Module& m) {
    stream << m.name << " " << kTypeName[m.type];
    for (const auto& to : m.destinations) {
      stream << " " << to->name;
    }
    return stream;
  }

  Message SendPulse(const int to_index, const Pulse pulse) {
    return Message{.from = *this,
                   .to = *destinations[to_index],
                   .pulse = pulse,
                   .to_index = to_index};
  }

  std::vector<Message> SendPulses(const Pulse pulse) {
    std::vector<Message> messages;
    for (int i = 0; i < destinations.size(); ++i) {
      messages.push_back(SendPulse(i, pulse));
    }
    return messages;
  }

  std::vector<Message> ReceivePulse(const Pulse pulse) {
    if (type == Type::STANDARD) {
      return {};
    } else if (type == Type::FLIP_FLOP) {
      if (pulse == Pulse::LOW) {
        const Pulse next_pulse = on ? Pulse::LOW : Pulse::HIGH;
        on = !on;
        return SendPulses(next_pulse);
      }
    } else if (type == Type::CONJUCTION) {
      const Pulse next_pulse =
          std::all_of(input_pulse_history.begin(), input_pulse_history.end(),
                      [](const Pulse p) { return p == Pulse::HIGH; })
              ? Pulse::LOW
              : Pulse::HIGH;
      return SendPulses(next_pulse);
    } else if (type == Type::BROADCASTER) {
      return SendPulses(pulse);
    }
    return {};
  }
};

std::istream& operator>>(
    std::istream& stream,
    std::pair<std::shared_ptr<Module>, std::vector<std::string>>& md) {
  auto& [mod, destinations] = md;
  mod = std::make_shared<Module>();
  Module& m = *mod;
  destinations.clear();

  std::string line;
  std::getline(stream, line);
  if (line.empty()) return stream;

  std::istringstream sin(line);
  std::string type_name;
  sin >> type_name;

  if (m.type = GetType(type_name[0])) {
    m.name = type_name.substr(1);
  } else {
    m.name = type_name;
  }
  if (m.name == kBroadcasterName) {
    m.type = Type::BROADCASTER;
  }

  sin.ignore(3);
  for (std::string to; sin.ignore(1) && std::getline(sin, to, ',');) {
    destinations.push_back(to);
  }

  return stream;
}

struct Machine {
  std::map<std::string, std::shared_ptr<Module>> module_by_name;

  Machine() {}

  friend std::istream& operator>>(std::istream& stream, Machine& machine) {
    std::vector<std::pair<std::shared_ptr<Module>, std::vector<std::string>>>
        mds;
    for (std::pair<std::shared_ptr<Module>, std::vector<std::string>> md;
         std::cin >> md;) {
      mds.push_back(md);
    }

    for (const auto& [m, destinations] : mds) {
      machine.module_by_name[m->name] = std::move(m);
    }

    for (const auto& [m, destinations] : mds) {
      Module& mod = *machine.module_by_name.find(m->name)->second;
      for (const std::string& d : destinations) {
        auto it = machine.module_by_name.find(d);
        if (it == machine.module_by_name.end()) {
          it = machine.module_by_name.emplace(d, std::make_shared<Module>(d))
                   .first;
        }
        std::shared_ptr<Module> d_mod = it->second;
        mod.destinations.push_back(d_mod);
        mod.index_on_destination_input.push_back(
            d_mod->input_pulse_history.size());
        d_mod->input_pulse_history.push_back(Pulse::LOW);
      }
    }

    machine.module_by_name[kButtonName] = std::make_shared<Module>();
    machine.module_by_name[kButtonName]->name = kButtonName;
    machine.module_by_name[kButtonName]->index_on_destination_input.push_back(
        0);
    machine.module_by_name[kBroadcasterName]->input_pulse_history.push_back(
        Pulse::LOW);

    return stream;
  }

  friend std::ostream& operator<<(std::ostream& stream,
                                  const Machine& machine) {
    for (const auto& [name, m] : machine.module_by_name) {
      std::cout << *m << "\n";
    }
    return stream;
  }

  std::pair<lli, lli> PushButton(std::ostringstream& sout) const {
    lli low_cnt = 0, high_cnt = 0;
    Module& broadcaster = *module_by_name.find(kBroadcasterName)->second;
    Module& button = *module_by_name.find(kButtonName)->second;

    int current_timestamp = 0;
    std::queue<Message> message_queue;
    auto ProcessMessage = [&current_timestamp, &message_queue, &sout, &low_cnt,
                           &high_cnt](const Message message) {
      if (message.pulse == Pulse::LOW)
        ++low_cnt;
      else
        ++high_cnt;

      if (message.timestamp > current_timestamp) {
        sout << "\n";
        current_timestamp = message.timestamp;
      }

      message.to.input_pulse_history
          [message.from.index_on_destination_input[message.to_index]] =
          message.pulse;
      sout << message.from.name << " -[" << kPulseName[message.pulse] << "]> "
           << message.to.name << "\n";

      std::vector<Message> messages = message.to.ReceivePulse(message.pulse);
      for (Message& m : messages) {
        m.timestamp = message.timestamp + 1;
        message_queue.push(m);
      }
    };

    ProcessMessage(Message{.from = button,
                           .to = broadcaster,
                           .pulse = Pulse::LOW,
                           .timestamp = current_timestamp,
                           .to_index = 0});
    while (!message_queue.empty()) {
      const Message m = message_queue.front();
      message_queue.pop();
      ProcessMessage(m);
    }

    return std::make_pair(low_cnt, high_cnt);
  }
};

int main() {
  Machine machine;
  std::cin >> machine;

  DEBUG std::cout << machine << "\n";

  lli low_sum = 0, high_sum = 0;
  for (int i = 0; i < kButtonPushes; ++i) {
    std::ostringstream sout;
    auto [low_cnt, high_cnt] = machine.PushButton(sout);
    low_sum += low_cnt;
    high_sum += high_cnt;
    DEBUG std::cout << "Press: " << i << "\n"
                    << sout.str() << "\n----------------------------------\n";
  }
  lli ans = low_sum * high_sum;
  std::cout << ans << "\n";

  return 0;
}
