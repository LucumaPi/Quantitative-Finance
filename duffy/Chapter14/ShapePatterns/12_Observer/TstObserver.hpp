using System;

public class TstObserver
{
    public static int Main(string[] args)
    {
		// Create a counter object
		Counter cnt = new Counter();
		
		// Just increase the counter without observing it
        cnt.IncreaseCounter();
		cnt.IncreaseCounter();
		cnt.IncreaseCounter();

		// Create an observer
		CounterObserver observer1 = new CounterObserver(cnt);

		// Increase the counter
        cnt.IncreaseCounter();
		cnt.IncreaseCounter();
		cnt.IncreaseCounter();

		// Create another observer
		CounterObserver observer2 = new CounterObserver(cnt);

		// Increase the counter
        cnt.IncreaseCounter();
		cnt.IncreaseCounter();
		cnt.IncreaseCounter();

		// remove the first observer
		cnt.DeleteObserver(observer1);

		// Increase the counter
        cnt.IncreaseCounter();
		cnt.IncreaseCounter();
		cnt.IncreaseCounter();

        return 0;
    }
}

