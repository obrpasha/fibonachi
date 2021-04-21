#include <iostream>
#include <vector>
#include <chrono>
#include <functional>


class Fibonachi
{
public:
  unsigned GetValue(unsigned n)
  {
      if (m_FibCache.size() <= n)
      {
          for(unsigned int i = m_FibCache.size() - 1; i < n; ++i)
          {
              const unsigned res = m_FibCache[m_FibCache.size() - 2] + m_FibCache[m_FibCache.size() - 1];
              m_FibCache.push_back(res);
          }

          return m_FibCache.back();
      }
      else
      {
          return m_FibCache[n];
      }
  }

private:
   static std::vector<unsigned int> m_FibCache;
};

std::vector<unsigned int> Fibonachi::m_FibCache(1, 1);

unsigned f1(unsigned n) 
{
  if (n == 0 || n == 1) 
  {
    return 1;
  }
  
  return f1(n - 1) + f1(n - 2);
}

Fibonachi f;

unsigned int f2(unsigned n)
{
    return f.GetValue(n);
}

unsigned f3(unsigned n)
{
  if (n == 0 || n == 1)
    return 1;

  unsigned prevPrev = 1; //0
  unsigned prev = 1; //0;

  unsigned res = 0;
  for (unsigned int i = 1; i<n; ++i)
  {
    res = prevPrev+prev;

    prevPrev = prev;
    prev = res;
  }

  return res;
}

void runner(unsigned n, std::function<unsigned(unsigned)> fibFn)
{
    auto startT = std::chrono::high_resolution_clock::now();

    for (unsigned i = 0; i < n; i++)
    {
        const unsigned fibN = rand() % n;
        unsigned res = fibFn(fibN);
        //std::cout << "Fib(" << i << ")" << res  << std::endl;
    }

    auto endT = std::chrono::high_resolution_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(endT - startT);

    std::cout << "-------------->Execution time: " << ms.count() << " (ms)" << std::endl;
}

int main()
{
    const unsigned n = 20000;

    //Run and evaluate execution time for logic only, not an output
    //f2 solution is faster
    //but it requires more memory
    //Memory is cheaper than CPU time, so
    //having increasing in performance is more effective
    //For n = 20000
    //f2 Execution time: 1 (ms)
    //f3 Execution time: 2807 (ms)

    //runner(n, f1);
    runner(n, f2);  //Execution time: 1 (ms)
    runner(n, f3);  //Execution time: 2807 (ms)

    return 0;
}
