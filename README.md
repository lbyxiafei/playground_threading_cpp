[toc]
# Terminology
### Mutex
- Mutual exclusion used to guard shared data. Allows only single thread to access resource or critical section.
- 类比: `更衣室`.
### Semaphore
- Limited permits for access to the collections of resources. Important distinction: can be used for signaling among threads.
- 类比：`苹果旗舰店限客50人`
### Deadlock
- 产生死锁的四个条件（参考：[钥匙保险箱问题](https://zhuanlan.zhihu.com/p/26945588)）：
    1. 互斥条件：一个资源每次只能被一个进程使用；
    2. 请求与保持条件：一个进程因请求资源而阻塞时，对已获得的资源保持不放；
    3. 不剥夺条件：进程已获得的资源，在没使用完之前，不能强行剥夺；
    4. 循环等待条件：多个进程之间形成一种互相循环等待资源的关系。
- [哲学家就餐问题](https://zh.wikipedia.org/wiki/%E5%93%B2%E5%AD%A6%E5%AE%B6%E5%B0%B1%E9%A4%90%E9%97%AE%E9%A2%98),这里引出了另一个概念：`活锁`
    - 活锁：所有哲学家同时拿起左边的叉子，即使加入了释放机制，最终也会是拿起来、等待、放下无限循环
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







