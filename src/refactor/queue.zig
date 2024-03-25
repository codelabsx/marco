
pub fn CreateQueue(comptime T: type) type {
    return struct {
        queue: [2]*T,

        fn queueExit() !void {

        }
    };
}



test "should return the queue" {

}



