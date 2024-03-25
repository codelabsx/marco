class EventLoop {
    constructor() {
        this.queue = [];
        this.stop = 0;
        this.wakeup = null;
    }

    wait() {
        return new Promise(resolve => {
            this.wakeup = () => {
                this.wakeup = null;
                resolve();
            }
        });
    }

    //停止事件循环
    setStop() {
        this.stop = 1;
        this.wakeup && this.wakeup();
    }

    handleTask() {
        if (this.queue.length === 0) {
            return 0;
        }

        const queue = this.queue;
        this.queue = [];

        while (queue.length) {
            const func = queue.shift();
            func();
        }
    }

    async run() { //使用异步组件避免卡死
        while (this.stop == 0) {
            this.handleTask();

            //可以退出
            if (this.stop == 1) {
                break;
            }

            //没有任务进行休息
            if (this.queue.length === 0) {
                await this.wait();
            }
        }

        //退出前可能还有任务处理
        this.handleTask();
    }
}

//新建一个事件循环系统
const eventSystem = new eventSystem();

//启动前生成的任务
eventSystem.enQueue(() => {
    console.log("1");
});

//模拟定时生成一个任务
setTimeout(() => {

}, 1000);

//启动事件循环
eventSystem.run();

//启动生成的任务
eventSystem.enQueue(() => {
    console.log('2');
})