const std = @import("std");

var stdout_buffer: [4096]u8 = undefined;
var stdout: *std.Io.Writer = undefined;

var stdin_buffer: [4096]u8 = undefined;
var stdin: *std.Io.Reader = undefined;

pub fn print(comptime format: []const u8, args: anytype) void {
    stdout.print(format, args) catch unreachable;
    stdout.flush() catch unreachable;
}

pub fn parseInt(comptime T: type, string: []const u8) T {
    return std.fmt.parseInt(T, string, 10) catch unreachable;
}

pub fn fastParseInt(string: []const u8) i32 {
    var ans: i32 = 0;
    for (string) |digit| {
        ans = ans * 10 + (digit - '0');
    }
    return ans;
}

pub fn printElapsedTimeNs(
    elapsed: std.Io.Duration,
    action: []const u8,
) void {
    print("{s} -> execution time: {d}ms | {d}us | {d}ns\n", .{
        action,
        elapsed.toMilliseconds(),
        elapsed.toMicroseconds(),
        elapsed.nanoseconds,
    });
}
pub fn printElapsedTime(
    elapsed: std.Io.Duration,
    action: []const u8,
) void {
    printElapsedTimeNs(elapsed, action);
}

pub fn naiveFindScalarPos(comptime T: type, slice: []const T, start_index: usize, value: T) ?usize {
    var i = start_index;
    while (i < slice.len and slice[i] != value) : (i += 1) {}
    if (i == slice.len) return null;
    return i;
}

pub fn readArray(
    io: std.Io,
    allocator: std.mem.Allocator,
) ![]i32 {
    const clock = std.Io.Clock.real;
    var start_time = clock.now(io);

    const input_string = try stdin.allocRemaining(
        allocator,
        .unlimited,
    );
    defer allocator.free(input_string);
    printElapsedTime(
        std.Io.Timestamp.untilNow(start_time, io, clock),
        "input_string read",
    );
    start_time = clock.now(io);

    // Manual parsing: ~0ms + ~80ms
    // var it: usize = 0;
    // const bp = std.mem.findScalar(u8, input_string, '\n').?;
    // const n = parseInt(usize, input_string[it..bp]);
    // it = bp + 1;
    // printElapsedTime(
    //     std.Io.Timestamp.untilNow(start_time, io, clock),
    //     "n read",
    // );
    // const array = try allocator.alloc(i32, n);
    // for (array) |*val| {
    //     // naiveFindScalarPos -> ~80ms
    //     const dp = naiveFindScalarPos(u8, input_string, it, ' ') orelse naiveFindScalarPos(u8, input_string, it, '\n').?;
    //     // std.mem.findScalarPos -> ~105ms
    //     // const dp = std.mem.findScalarPos(u8, input_string, it, ' ') orelse std.mem.findScalarPos(u8, input_string, it, '\n').?;
    //     val.* = fastParseInt(input_string[it..dp]);
    //     it = dp + 1;
    // }

    // Semi manual parsing: ~0ms + ~100ms
    // const bp = std.mem.findScalar(u8, input_string, '\n').?;
    // const n = parseInt(usize, input_string[0..bp]);
    // var value_it = std.mem.tokenizeScalar(u8, input_string[bp + 1 .. input_string.len - 1], ' ');
    // printElapsedTime(
    //     std.Io.Timestamp.untilNow(start_time, io, clock),
    //     "n read",
    // );
    // const array = try allocator.alloc(i32, n);
    // for (array) |*val| {
    //     // val.* = parseInt(i32, value_it.next().?);
    //     val.* = fastParseInt(value_it.next().?);
    // }

    // Full tokenization: ~20ms + ~100ms
    var lines_it = std.mem.tokenizeScalar(u8, input_string, '\n');
    const n = parseInt(usize, lines_it.next().?);
    const array_str = lines_it.next().?;
    var value_it = std.mem.tokenizeScalar(u8, array_str, ' ');
    printElapsedTime(
        std.Io.Timestamp.untilNow(start_time, io, clock),
        "n read",
    );
    const array = try allocator.alloc(i32, n);
    for (array) |*val| {
        // val.* = parseInt(i32, value_it.next().?);
        val.* = fastParseInt(value_it.next().?);
    }

    printElapsedTime(
        std.Io.Timestamp.untilNow(start_time, io, clock),
        "n + array read",
    );

    return array;
}

pub fn main(init: std.process.Init) !void {
    const io = init.io;
    var stdout_writer = std.Io.File.stdout().writer(io, &stdout_buffer);
    stdout = &stdout_writer.interface;
    // const file = try std.Io.Dir.openFile(std.Io.Dir.cwd(), io, "big_in", .{ .mode = .read_only });
    // defer file.close(io);
    // var stdin_reader = file.reader(io, &stdin_buffer);
    var stdin_reader = std.Io.File.stdin().reader(io, &stdin_buffer);
    stdin = &stdin_reader.interface;

    const gpa = init.gpa;
    // var debug_allocator = std.heap.DebugAllocator(.{}){};
    // const gpa = debug_allocator.allocator();
    // defer std.debug.assert(debug_allocator.de == .ok);

    var array = try readArray(io, gpa);
    defer gpa.free(array);
    print("array[0:4] (size = {d}): {any}\n", .{ array.len, array[0..5] });
}
