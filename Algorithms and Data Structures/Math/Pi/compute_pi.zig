const std = @import("std");
const BigInt = std.math.big.int.Managed;
const Allocator = std.mem.Allocator;
var gpa = std.heap.GeneralPurposeAllocator(.{}){};
const gpa_alloc = gpa.allocator();

pub const Decimal = struct {
    allocator: Allocator,
    a: BigInt,
    b: BigInt,
    tmp: BigInt,
    precision: BigInt,

    pub fn init(allocator: Allocator, a: i32, b: i32) !Decimal {
        var a_big = try BigInt.init(allocator);
        try a_big.set(a);
        var b_big = try BigInt.init(allocator);
        try b_big.set(b);
        const tmp_big = try BigInt.init(allocator);
        var precision_big = try BigInt.init(allocator);
        try precision_big.set(std.math.pow(i64, 10, 16));
        return Decimal{
            .allocator = allocator,
            .a = a_big,
            .b = b_big,
            .tmp = tmp_big,
            .precision = precision_big,
        };
    }

    pub fn deinit(self: *Decimal) void {
        self.a.deinit();
        self.b.deinit();
        self.tmp.deinit();
        self.precision.deinit();
    }

    pub fn toString(self: *Decimal, allocator: Allocator) ![]u8 {
        try self.tmp.copy(self.a.toConst());
        try self.tmp.mul(&self.tmp, &self.precision);
        try self.tmp.divTrunc(&self.precision, &self.tmp, &self.b);
        return self.tmp.toString(allocator, 10, .lower);
    }
};

pub fn main() !void {
    defer std.debug.assert(gpa.deinit() == .ok);

    var b = try Decimal.init(gpa_alloc, 1, 7);
    defer b.deinit();
    // try b.sqrt();

    const b_str = try b.toString(gpa_alloc);
    defer gpa_alloc.free(b_str);
    std.debug.print("hello! {s}\n", .{b_str});
}
