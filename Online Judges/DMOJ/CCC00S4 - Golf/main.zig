const std = @import("std");
const kMaxDistance: i32 = 5280;

pub fn parseInt(line: []const u8) !i32 {
    return std.fmt.parseInt(i32, line[0..], 10);
}

const TestCaseError = error{NotFound};
const TestCase = struct {
    distance: i32,
    clubs_count: i32,
    clubs: []i32,
    memo: []i32,

    fn deinit(self: *const TestCase, gpa: std.mem.Allocator) void {
        gpa.free(self.clubs);
        gpa.free(self.memo);
    }

    fn read(input_it: *std.mem.SplitIterator(u8, std.mem.DelimiterType.sequence), gpa: std.mem.Allocator) !TestCase {
        var test_case: TestCase = undefined;
        const distance_line = input_it.next();
        if (distance_line == null) return TestCaseError.NotFound;
        if (distance_line.?.len == 0) return TestCaseError.NotFound;

        test_case.distance = try parseInt(distance_line.?);
        test_case.clubs_count = try parseInt(input_it.next().?);
        test_case.clubs = try gpa.alloc(i32, @intCast(test_case.clubs_count));
        for (test_case.clubs) |*club| {
            club.* = try parseInt(input_it.next().?);
        }
        test_case.memo = try gpa.alloc(i32, kMaxDistance + 1);
        for (test_case.memo) |*v| {
            v.* = -1;
        }
        return test_case;
    }

    fn calc(self: *const TestCase, d: i32) i32 {
        if (d > self.distance) {
            return 1e9;
        }
        if (d == self.distance) {
            return 0;
        }
        const ans: *i32 = &self.memo[@intCast(d)];
        if (ans.* != -1) {
            return ans.*;
        }
        ans.* = 1e9;

        for (self.clubs) |club| {
            ans.* = @min(ans.*, self.calc(d + club) + 1);
        }
        return ans.*;
    }
    fn solve(self: *const TestCase) i32 {
        return self.calc(0);
    }
};

pub fn main() !void {
    const in = std.io.getStdIn().reader();
    const out = std.io.getStdOut().writer();

    var general_purpose = std.heap.GeneralPurposeAllocator(.{}){};
    defer std.debug.assert(general_purpose.deinit() == .ok);
    const gpa = general_purpose.allocator();

    const inputLines = try in.readAllAlloc(gpa, 100);
    defer gpa.free(inputLines);

    var input_it = std.mem.splitSequence(u8, inputLines[0..], "\r\n");
    while (TestCase.read(&input_it, gpa)) |test_case| {
        defer test_case.deinit(gpa);
        // try out.print("{} {} {any}\n", .{ test_case.distance, test_case.clubs_count, test_case.clubs });

        const ans = test_case.solve();
        if (ans == 1e9) {
            try out.print("Roberta acknowledges defeat.\n", .{});
        } else {
            try out.print("Roberta wins in {} strokes.\n", .{ans});
        }

        _ = input_it.next();
    } else |_| {}
}
