using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using AllInOneDll;
using CppCliDll;
using ManagedDll;

namespace TestConsole
{
    class Program
    {
        private static List<uint> _tasksLoopCounts;

        private static List<double> _managedWorkerWorkingSeconds;
        private static List<double> _cppCliWorkerWorkingSeconds;
        private static List<double> _allInOneWorkerWorkingSeconds;

        static Program()
        {
            _tasksLoopCounts = new List<uint>();

            for (uint taskLoopCount = 10000; taskLoopCount < 50000; taskLoopCount += 1000)
            {
                _tasksLoopCounts.Add(taskLoopCount);
            }

            _managedWorkerWorkingSeconds = new List<double>();
            _cppCliWorkerWorkingSeconds = new List<double>();
            _allInOneWorkerWorkingSeconds = new List<double>();
        }

        static void Main(string[] args)
        {
            Console.Title = "Exposing native to managed - performance tests";

            MultipleCallsTest();
            OneCallTest();
            MultipleSyncCallsTest();

            WriteWorkersWorkingSeconds();

            Console.WriteLine("Press <Enter> to quit.");
            Console.ReadLine();
        }

        private static void WriteWorkersWorkingSeconds()
        {
            Console.WriteLine("Managed worker (P/Invoke) - working seconds:");
            foreach (double managedWorkerSeconds in _managedWorkerWorkingSeconds)
            {
                Console.WriteLine("\t{0}", managedWorkerSeconds);
            }
            Console.WriteLine();

            Console.WriteLine("C++/CLI worker - working seconds:");
            foreach (double cppCliWorkerSeconds in _cppCliWorkerWorkingSeconds)
            {
                Console.WriteLine("\t{0}", cppCliWorkerSeconds);
            }
            Console.WriteLine();

            Console.WriteLine("All-in-one (C++/CLI) worker - working seconds:");
            foreach (double allInOneWorkerSeconds in _allInOneWorkerWorkingSeconds)
            {
                Console.WriteLine("\t{0}", allInOneWorkerSeconds);
            }
            Console.WriteLine();
        }

        #region MultipleCallsTest

        private static void MultipleCallsTest()
        {
            MultipleCallsTest_TestAllInOneWorker();
            Console.WriteLine();
            MultipleCallsTest_TestCppCliWorker();
            Console.WriteLine();
            MultipleCallsTest_TestManagedWorker();
            Console.WriteLine();

            MultipleCallsTest_TestManagedWorker();
            Console.WriteLine();
            MultipleCallsTest_TestCppCliWorker();
            Console.WriteLine();
            MultipleCallsTest_TestAllInOneWorker();
            Console.WriteLine();
        }

        static void MultipleCallsTest_TestAllInOneWorker()
        {
            Console.WriteLine("Multiple calls - All-in-one (C++/CLI) worker test:");

            using (AllInOneWorker worker = new AllInOneWorker())
            {
                Console.Write("Starting...");

                worker.Start();

                foreach (uint taskLoopCount in _tasksLoopCounts)
                {
                    worker.QueueWorkerTask(taskLoopCount, taskLoopCount);
                }

                worker.Stop();

                Console.WriteLine(" - Finished.");

                worker.PrintStatistics();

                _allInOneWorkerWorkingSeconds.Add(worker.GetWorkingSeconds());
            }
        }

        static void MultipleCallsTest_TestCppCliWorker()
        {
            Console.WriteLine("Multiple calls - C++/CLI worker test:");

            using (CppCliWorker worker = new CppCliWorker())
            {
                Console.Write("Starting...");

                worker.Start();

                foreach (uint taskLoopCount in _tasksLoopCounts)
                {
                    worker.QueueWorkerTask(taskLoopCount, taskLoopCount);
                }

                worker.Stop();

                Console.WriteLine(" - Finished.");

                worker.PrintStatistics();

                _cppCliWorkerWorkingSeconds.Add(worker.GetWorkingSeconds());
            }
        }

        static void MultipleCallsTest_TestManagedWorker()
        {
            Console.WriteLine("Multiple calls - Managed worker (P/Invoke) test:");

            using (ManagedWorker worker = new ManagedWorker())
            {
                Console.Write("Starting...");

                worker.Start();

                foreach (uint taskLoopCount in _tasksLoopCounts)
                {
                    worker.QueueWorkerTask(taskLoopCount, taskLoopCount);
                }

                worker.Stop();

                Console.WriteLine(" - Finished.");

                worker.PrintStatistics();

                _managedWorkerWorkingSeconds.Add(worker.GetWorkingSeconds());
            }
        }

        #endregion

        #region OneCallTest

        private static void OneCallTest()
        {
            OneCallTest_TestAllInOneWorker();
            Console.WriteLine();
            OneCallTest_TestCppCliWorker();
            Console.WriteLine();
            OneCallTest_TestManagedWorker();
            Console.WriteLine();

            OneCallTest_TestManagedWorker();
            Console.WriteLine();
            OneCallTest_TestCppCliWorker();
            Console.WriteLine();
            OneCallTest_TestAllInOneWorker();
            Console.WriteLine();
        }

        static void OneCallTest_TestAllInOneWorker()
        {
            Console.WriteLine("One call - All-in-one (C++/CLI) worker test:");

            using (AllInOneWorker worker = new AllInOneWorker())
            {
                Console.Write("Starting...");

                worker.Start();

                worker.QueueDemoWorkerTasks();

                worker.Stop();

                Console.WriteLine(" - Finished.");

                worker.PrintStatistics();

                _allInOneWorkerWorkingSeconds.Add(worker.GetWorkingSeconds());
            }
        }

        static void OneCallTest_TestCppCliWorker()
        {
            Console.WriteLine("One call - C++/CLI worker test:");

            using (CppCliWorker worker = new CppCliWorker())
            {
                Console.Write("Starting...");

                worker.Start();

                worker.QueueDemoWorkerTasks();

                worker.Stop();

                Console.WriteLine(" - Finished.");

                worker.PrintStatistics();

                _cppCliWorkerWorkingSeconds.Add(worker.GetWorkingSeconds());
            }
        }

        static void OneCallTest_TestManagedWorker()
        {
            Console.WriteLine("One call - Managed worker (P/Invoke) test:");

            using (ManagedWorker worker = new ManagedWorker())
            {
                Console.Write("Starting...");

                worker.Start();

                worker.QueueDemoWorkerTasks();

                worker.Stop();

                Console.WriteLine(" - Finished.");

                worker.PrintStatistics();

                _managedWorkerWorkingSeconds.Add(worker.GetWorkingSeconds());
            }
        }

        #endregion

        #region MultipleSyncCallsTest

        private static void MultipleSyncCallsTest()
        {
            MultipleSyncCallsTest_TestAllInOneWorker();
            Console.WriteLine();
            MultipleSyncCallsTest_TestCppCliWorker();
            Console.WriteLine();
            MultipleSyncCallsTest_TestManagedWorker();
            Console.WriteLine();

            MultipleSyncCallsTest_TestManagedWorker();
            Console.WriteLine();
            MultipleSyncCallsTest_TestCppCliWorker();
            Console.WriteLine();
            MultipleSyncCallsTest_TestAllInOneWorker();
            Console.WriteLine();
        }

        static void MultipleSyncCallsTest_TestAllInOneWorker()
        {
            Console.WriteLine("Synchronous calls - All-in-one (C++/CLI) worker test:");

            using (AllInOneWorker worker = new AllInOneWorker())
            {
                Console.Write("Starting...");

                worker.Start();

                Parallel.ForEach(_tasksLoopCounts, t => { worker.ExecuteWorkerTask(t, t); });

                worker.Stop();

                Console.WriteLine(" - Finished.");

                worker.PrintStatistics();

                _allInOneWorkerWorkingSeconds.Add(worker.GetWorkingSeconds());
            }
        }

        static void MultipleSyncCallsTest_TestCppCliWorker()
        {
            Console.WriteLine("Synchronous calls - C++/CLI worker test:");

            using (CppCliWorker worker = new CppCliWorker())
            {
                Console.Write("Starting...");

                worker.Start();

                Parallel.ForEach(_tasksLoopCounts, t => { worker.ExecuteWorkerTask(t, t); });

                worker.Stop();

                Console.WriteLine(" - Finished.");

                worker.PrintStatistics();

                _cppCliWorkerWorkingSeconds.Add(worker.GetWorkingSeconds());
            }
        }

        static void MultipleSyncCallsTest_TestManagedWorker()
        {
            Console.WriteLine("Synchronous calls - Managed worker (P/Invoke) test:");

            using (ManagedWorker worker = new ManagedWorker())
            {
                Console.Write("Starting...");

                worker.Start();

                Parallel.ForEach(_tasksLoopCounts, t => { worker.ExecuteWorkerTask(t, t); });

                worker.Stop();

                Console.WriteLine(" - Finished.");

                worker.PrintStatistics();

                _managedWorkerWorkingSeconds.Add(worker.GetWorkingSeconds());
            }
        }

        #endregion
    }
}
