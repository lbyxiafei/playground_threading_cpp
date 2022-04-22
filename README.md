[toc]
# Terminology
### Mutex
- Mutual exclusion used to guard shared data. Allows only single thread to access resource or critical section.
- Analogy: `changing room`.
### Semaphore
- x
### Deadlock
- y
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







