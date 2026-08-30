For a second I was afraid of the 100^4, then I remembered the last one is forced
so it's just 100^3 or 10^6 hahahaha.

It runs in 5ms with O2 \o/.
Because of the clipping on negatives, I'm having a hard time imagining something
better than a brute force. Maybe some kind of MeetInTheMiddle could make it a
bit faster.

Anyways, I finally digged into how to forward arguments to `std::format`.
For `std::println("{:{}}", str, padding_size)` works by default but I wanted to
do it on a custom struct.
Honestly, it's pretty convoluted and the documentation is really bad.
Anyways, IIUC this dynamic case, we just need to save the argument id in the
parsing stage (along with any constant metadata we need) and then retrieve it
during the formatting stage.
Curiously, we need to do it in a std::visit but I suppose this is because the
arguments are variants and `std::format` wants us to handle all cases.