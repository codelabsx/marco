const std = @import("std");
const expect = std.testing.expect;


pub fn create_heap(comptime T: type) !type {

}



const Node = struct {
    value: u32,
    child: ?*Node,       //指向该节点的第一个儿子
    sibling: ?*Node,     //sibling指向改节点的下一个兄弟

    const Self = @This();

    pub fn meld(self: *Self, node: *Node) ?*Self {
        
        if (self.value > node.value) {
            const temp = self.value;
            self.value = node.value;
            node.value = temp;

            //将node的兄弟设置为slef原来的孩子
            node.sibling = self.child;
            
            //将node设置为自己的孩子
            self.child = node;
            
            return self;
        }
        
        return self;
    }

    //删除最小值
    pub fn merges(self: *Self, x: ?*Node) ?*Self {
        
        //如果当前树为空, 或者它的兄弟为null, 直接返回
        if (x == null or x.?.sibling == null) {
            return x;
        }

        var y: ?*Node = x.?.sibling;
        var c: ?*Node = y.?.sibling;


        return 

    }
};


test "syntax is right" {
    var c = Node{.value=5, .child=null, .sibling=null};
    var x = Node{.value=4, .child=&c, .sibling=null};
    var y = Node{.value=2, .child=null, .sibling=null};

    try expect(x.meld(&y).?.value == 2);
    try expect(x.child.?.value == 4);
    try expect(y.sibling.?.value == 5);
}

