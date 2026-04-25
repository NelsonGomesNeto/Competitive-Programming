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
        "array read",
    );

    return array;
}

pub fn mergeWithTemp(
    comptime T: type,
    array: []T,
    tmp: []T,
    alo: usize,
    ahi: usize,
    blo: usize,
    bhi: usize,
) void {
    var i = alo;
    var j = blo;
    var k = alo;
    while (i <= ahi or j <= bhi) {
        if (i <= ahi and j <= bhi) {
            if (array[i] <= array[j]) {
                tmp[k] = array[i];
                i += 1;
            } else {
                tmp[k] = array[j];
                j += 1;
            }
            k += 1;
        } else if (i <= ahi) {
            while (i <= ahi) : ({
                k += 1;
                i += 1;
            }) {
                tmp[k] = array[i];
            }
        } else {
            while (j <= bhi) : ({
                k += 1;
                j += 1;
            }) {
                tmp[k] = array[j];
            }
        }
    }
    @memcpy(array[alo .. bhi + 1], tmp[alo .. bhi + 1]);
    // @memmove(array[alo .. bhi + 1], tmp[alo .. bhi + 1]);
    // std.mem.copyForwards(T, array[alo .. bhi + 1], tmp[alo .. bhi + 1]);
    // for (alo..bhi + 1) |l| {
    //     array[l] = tmp[l];
    // }
}

pub fn mergeSortInternal(comptime T: type, array: []T, tmp: []T) void {
    if (array.len <= 1) return;

    const mid = array.len >> 1;
    mergeSortInternal(T, array[0..mid], tmp[0..mid]);
    mergeSortInternal(T, array[mid..], tmp[mid..]);

    mergeWithTemp(T, array, tmp, 0, mid - 1, mid, array.len - 1);
    // mergeNoTemp(T, array, 0, mid - 1, mid, array.len - 1);
}

pub fn mergeSort(
    comptime T: type,
    allocator: std.mem.Allocator,
    array: []T,
) void {
    const tmp = allocator.alloc(T, array.len) catch unreachable;
    defer allocator.free(tmp);
    mergeSortInternal(T, array, tmp);
}

pub fn iterativeMergeSort(
    comptime T: type,
    allocator: std.mem.Allocator,
    array: []T,
) void {
    const tmp = allocator.alloc(T, array.len) catch unreachable;
    defer allocator.free(tmp);

    var block_size: usize = 2;
    while (block_size < array.len) : (block_size <<= 1) {
        var lo: usize = 0;
        while (lo < array.len) : (lo += block_size) {
            if (lo + block_size > array.len) {
                var j = lo + 1;
                const mid = while (j < array.len) : (j += 1) {
                    if (array[j - 1] > array[j]) break j - 1;
                } else array.len;
                if (mid == array.len) continue;
                mergeWithTemp(T, array, tmp, lo, mid, mid + 1, array.len - 1);
            } else {
                const hi = @min(lo + block_size, array.len) - 1;
                const mid = (lo + hi) >> 1;
                mergeWithTemp(T, array, tmp, lo, mid, mid + 1, hi);
            }
        }
    }
    const hi = array.len - 1;
    const mid = (block_size >> 1) - 1;
    mergeWithTemp(T, array, tmp, 0, mid, mid + 1, hi);
}

pub fn stdSort(
    comptime T: type,
    _: std.mem.Allocator,
    array: []T,
) void {
    std.mem.sort(T, array, {}, std.sort.asc(T));
}

const kExecutions = 30;

pub fn SortFn(comptime T: type) type {
    return struct {
        name: []const u8,
        sort_function: *const fn (
            std.mem.Allocator,
            []T,
        ) void,
        const Self = @This();

        pub fn init(
            comptime name: []const u8,
            comptime sort_function: *const fn (
                comptime type,
                std.mem.Allocator,
                []T,
            ) void,
        ) SortFn(T) {
            return .{
                .name = name,
                .sort_function = struct {
                    fn wrapper(allocator: std.mem.Allocator, array: []T) void {
                        return sort_function(T, allocator, array);
                    }
                }.wrapper,
            };
        }

        pub fn evaluate(
            self: *const Self,
            io: std.Io,
            allocator: std.mem.Allocator,
            original_array: []const T,
        ) !void {
            const description = try std.fmt.allocPrint(
                allocator,
                "array sorted with {s}",
                .{self.name},
            );
            defer allocator.free(description);

            const array = try allocator.alloc(T, original_array.len);
            defer allocator.free(array);

            const clock = std.Io.Clock.real;
            var average_time = std.Io.Duration.zero;
            for (0..kExecutions) |_| {
                @memcpy(array, original_array);
                const start_time = clock.now(io);
                self.sort_function(allocator, array);
                average_time.nanoseconds +=
                    std.Io.Timestamp.durationTo(
                        start_time,
                        clock.now(io),
                    ).nanoseconds;
            }
            average_time.nanoseconds = @divTrunc(
                average_time.nanoseconds,
                kExecutions,
            );
            printElapsedTimeNs(average_time, description);

            std.debug.assert(std.sort.isSorted(T, array, {}, std.sort.asc(T)));
        }
    };
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

    const sort_functions = [_]SortFn(i32){
        SortFn(i32).init(
            "MergeSort",
            mergeSort,
        ),
        SortFn(i32).init(
            "IterativeMergeSort",
            iterativeMergeSort,
        ),
        SortFn(i32).init(
            "StdSort",
            stdSort,
        ),
    };
    for (sort_functions) |sort_function| {
        try sort_function.evaluate(io, gpa, array);
    }
}
