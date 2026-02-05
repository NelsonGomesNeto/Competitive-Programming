const std = @import("std");
var gpa = std.heap.GeneralPurposeAllocator(.{}){};
const allocator = gpa.allocator();

var stdout_buffer: [4096]u8 = undefined;
var stdout_writer = std.fs.File.stdout().writer(&stdout_buffer);
const stdout = &stdout_writer.interface;

var stdin_buffer: [4096]u8 = undefined;
var stdin_reader = std.fs.File.stdin().reader(&stdin_buffer);
const stdin = &stdin_reader.interface;

pub fn print(comptime format: []const u8, args: anytype) void {
    // const output = std.fmt.allocPrint(allocator, format, args) catch unreachable;
    // defer allocator.free(output);
    // std.fs.File.stdout().writeAll(output) catch unreachable;

    stdout.print(format, args) catch unreachable;
    stdout.flush() catch unreachable;
}

pub fn parseInt(comptime T: type, string: []const u8) T {
    return std.fmt.parseInt(T, string, 10) catch unreachable;
}

pub fn printElapsedTimeNs(
    elapsed: u64,
    action: []const u8,
) void {
    print("{s} -> execution time: {d}ms | {d}us | {d}ns\n", .{
        action,
        elapsed / std.time.ns_per_ms,
        elapsed / std.time.ns_per_us,
        elapsed,
    });
}
pub fn printElapsedTime(
    timer: *std.time.Timer,
    action: []const u8,
) void {
    printElapsedTimeNs(timer.read(), action);
}

pub fn readArray() ![]i32 {
    var timer = try std.time.Timer.start();

    const input_string = try stdin.allocRemaining(
        allocator,
        .unlimited,
    );
    defer allocator.free(input_string);
    printElapsedTime(&timer, "input_string read");
    timer.reset();

    var lines_it = std.mem.tokenizeScalar(u8, input_string, '\n');

    const n = parseInt(usize, lines_it.next().?);
    const array = try allocator.alloc(i32, n);

    var value_it = std.mem.tokenizeScalar(u8, lines_it.next().?, ' ');
    for (array) |*val| {
        val.* = parseInt(i32, value_it.next().?);
    }
    printElapsedTime(&timer, "array read");

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

pub fn mergeSort(comptime T: type, array: []T) void {
    const tmp = allocator.alloc(T, array.len) catch unreachable;
    defer allocator.free(tmp);
    mergeSortInternal(T, array, tmp);
}

pub fn iterativeMergeSort(comptime T: type, array: []T) void {
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

pub fn stdSort(comptime T: type, array: []T) void {
    std.mem.sort(T, array, {}, std.sort.asc(T));
}

const kExecutions = 30;

pub fn SortFn(comptime T: type) type {
    return struct {
        name: []const u8,
        function: *const fn ([]T) void,

        const Self = @This();

        pub fn evaluate(self: *const Self, original_array: []const T) !void {
            const description = try std.fmt.allocPrint(
                allocator,
                "array sorted with {s}",
                .{self.name},
            );
            defer allocator.free(description);

            const array = try allocator.alloc(T, original_array.len);
            defer allocator.free(array);

            var average_time: u64 = 0;
            for (0..kExecutions) |_| {
                @memcpy(array, original_array);
                var timer = try std.time.Timer.start();
                self.function(array);
                average_time += timer.read();
            }
            average_time /= kExecutions;
            printElapsedTimeNs(average_time, description);

            std.debug.assert(std.sort.isSorted(T, array, {}, std.sort.asc(T)));
        }
    };
}
pub fn sortFn(
    comptime T: type,
    comptime name: []const u8,
    comptime function: *const fn (comptime type, []T) void,
) SortFn(T) {
    return .{
        .name = name,
        .function = struct {
            fn wrapper(array: []T) void {
                return function(T, array);
            }
        }.wrapper,
    };
}

pub fn main() !void {
    defer std.debug.assert(gpa.deinit() == .ok);

    var array = try readArray();
    defer allocator.free(array);
    print("array: {any}\n", .{array[0..5]});

    const sort_functions = [_]SortFn(i32){
        sortFn(
            i32,
            "MergeSort",
            mergeSort,
        ),
        sortFn(
            i32,
            "IterativeMergeSort",
            iterativeMergeSort,
        ),
        sortFn(
            i32,
            "StdSort",
            stdSort,
        ),
    };
    for (sort_functions) |sort_function| {
        try sort_function.evaluate(array);
    }
}
