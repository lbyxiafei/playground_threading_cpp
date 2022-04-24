[toc]
# Terminology
### Mutex
- 一句话：`保护共享资源`
- Mutual exclusion used to guard shared data. Allows only single thread to access resource or critical section.
- 类比: `更衣室`.
### Semaphore
- 一句话：`调度线程`
- Limited permits for access to the collections of resources. Important distinction: can be used for signaling among threads.
- 类比：`苹果旗舰店限客50人`
### Conditional Variable
- 条件锁，本质上还是锁，它的用途，还是围绕“共享资源”的。条件锁最典型的用途就是：防止不停地循环去判断一个共享资源是否满足某个条件。
    - 比如还是买票的例子：我们除了买票的线程外，现在再加一个线程：如果票数等于零，那么就要挂出“票已售完”的牌子。这种情况下如果没有条件锁，我们就不得不在“挂牌子”这个线程里不断地lock和unlock而在大多数情况下票数总是不等于零，这样的结果就是：占用了很多CPU资源但是大多数时候什么都没做。
    - 另外，假如我们还有一个线程，是在票数等于零时向上级部门申请新的票。同理，问题和上面的一样。而如果有了条件锁，我们就可以避免这种问题，而且还可以一次性地通知所有被条件锁锁住的线程。
- 这里有个问题，是关于条件锁的：pthread_cond_wait 为什么需要传递 mutex 参数？不清楚条件锁的朋友可以看一下。
- 总之请记住：**条件锁，是为了避免绝大多数情况下都是lock -> 判断条件 -> unlock的这种很占资源但又不干什么事情的线程。** 它和semaphore的用途是不同的。简而言之，锁是服务于共享资源的；而semaphore是服务于多个线程间的执行的逻辑顺序的。

### Deadlock
- 产生死锁的四个条件（参考：[钥匙保险箱问题](https://zhuanlan.zhihu.com/p/26945588)）：
    1. 互斥条件：一个资源每次只能被一个进程使用；
    2. 请求与保持条件：一个进程因请求资源而阻塞时，对已获得的资源保持不放；
    3. 不剥夺条件：进程已获得的资源，在没使用完之前，不能强行剥夺；
    4. 循环等待条件：多个进程之间形成一种互相循环等待资源的关系。
- [哲学家就餐问题](https://zh.wikipedia.org/wiki/%E5%93%B2%E5%AD%A6%E5%AE%B6%E5%B0%B1%E9%A4%90%E9%97%AE%E9%A2%98),这里引出了另一个概念：`活锁`
    - 活锁：所有哲学家同时拿起左边的叉子，即使加入了释放机制，最终也会是拿起来、等待、放下无限循环
# 灵魂拷问
### 为何需要多线程？
- 快
    - 例子：泡茶
        - 煮水和准备茶包可以同时进行
### 问题是什么？
- 当遇到线程间共享数据时，会产生：data race
    - 例子：计数器
        - 多线程更新计数器的时候，总次数会小于实际写入次数之和
### 怎样解决？
- 锁、mutex、semaphore

# Async & Await
- Await a `task`
    - `Async enables keyword await, and changes how methods results are handled, that's all!`
    - 如果有await，则pause and wait；如果无，则继续运行后续程序，直到遇到await task
        <details><summary>code snippet</summary>

        ```csharp
        public async Task Run()
        {
            Console.WriteLine("MyApp...");

            var waterTask = BoilingWater();
            var teaTask = MakeTea();

            await teaTask;  // 如果没有这两行，则直接打印MyApp!
            await waterTask;
            Console.WriteLine("MyApp!");
        }

        public async Task<string> BoilingWater()
        {
            Console.WriteLine("Water...");

            await Task.Delay(2000).ConfigureAwait(false);
            Console.WriteLine("Water!");

            return "water";
        }

        public async Task<string> MakeTea()
        {
            Console.WriteLine("Tea...");

            await Task.Delay(2000).ConfigureAwait(false);
            Console.WriteLine("Tea!");

            return "tea";
        }
        ```

        </details>

# Reference
- [Async and Await](https://blog.stephencleary.com/2012/02/async-and-await.html)
- [关于configureawait在UI/Context中的必要性(Deadlock)](https://medium.com/bynder-tech/c-why-you-should-use-configureawait-false-in-your-library-code-d7837dce3d7f)







