# PALA

> 给定一个长度为 N (N = 100,000) 的整数数组 S, 有 M (M >= 2) 个 workers 并发访问 S 并更新 S. 每个 worker 重复 10,000 次如下操作:
> 1. 随机生成 i, j, 0 <= i, j < 100,000;
> 2. 更新 S 使得 S(j) = S(i) + S(i+1) + S(i+2); 如果 i + 1 或者 i + 2 越界, 则用 (i+1) % N 或者 (i+2) % N;
>
> 提示
> 1. 请考虑并发保护, 即读取 S(i), S(i+1), S(i+2) 和更新 S(j) 为原子操作; *参考 two-phase locking 算法: [Two-phase locking - Wikipedia](https://en.wikipedia.org/wiki/Two-phase_locking)
> 2. 注意锁的粒度; 每个 worker 一次只读 3 个元素, 写 1 个元素; 共有 100,000 个元素; 并发 workers 同时访问同一元素的概率很低; 采用细粒度的锁, 可以降低冲突, 提高并发度;
> 3. 注意读锁和写锁的区别;
> 4. j 有可能落在 [i, i+2] 区间;
> 5. 附加思考: 会出现死锁吗? 如何避免.
