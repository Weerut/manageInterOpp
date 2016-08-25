using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace ManagedDll
{
    public class ManagedWorker:IDisposable
    {
        protected uint _workerId;

        #region UnmanagedDll imports
        [DllImport("NativeDll.dll", EntryPoint = "CreateWorker")]
        protected static extern uint _CreateWorker();

        [DllImport("NativeDll.dll", EntryPoint = "DeleteWorker", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void _DeleteWorker(uint workerId);

        [DllImport("NativeDll.dll", EntryPoint = "Start", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void _Start(uint workerId);

        [DllImport("NativeDll.dll", EntryPoint = "Stop", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void _Stop(uint workerId);

        [DllImport("NativeDll.dll", EntryPoint = "QueueDemoWorkerTasks", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void _QueueDemoWorkerTasks(uint workerId);

        [DllImport("NativeDll.dll", EntryPoint = "QueueWorkerTask", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void _QueueWorkerTask(uint workerId, uint outerLoopCount, uint innerLoopCount);

        [DllImport("NativeDll.dll", EntryPoint = "ExecuteWorkerTask", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void _ExecuteWorkerTask(uint workerId, uint outerLoopCount, uint innerLoopCount);

        [DllImport("NativeDll.dll", EntryPoint = "PrintStatistics", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void _PrintStatistics(uint workerId);

        [DllImport("NativeDll.dll", EntryPoint = "GetWorkingSeconds", CallingConvention = CallingConvention.Cdecl)]
        protected static extern double _GetWorkingSeconds(uint workerId);
        #endregion

        public ManagedWorker()
        {
            _workerId = _CreateWorker();
        }

        ~ManagedWorker() // Finalize
        {
            Dispose();
        }

        public void Dispose()
        {
            _DeleteWorker(_workerId);
        }

        public void Start()
        {
            _Start(_workerId);
        }

        public void Stop()
        {
            _Stop(_workerId);
        }

        public void QueueDemoWorkerTasks()
        {
            _QueueDemoWorkerTasks(_workerId);
        }

        public void QueueWorkerTask(uint outerLoopCount, uint innerLoopCount)
        {
            _QueueWorkerTask(_workerId, outerLoopCount, innerLoopCount);
        }

        public void ExecuteWorkerTask(uint outerLoopCount, uint innerLoopCount)
        {
            _ExecuteWorkerTask(_workerId, outerLoopCount, innerLoopCount);
        }

        public void PrintStatistics()
        {
            _PrintStatistics(_workerId);
        }

        public double GetWorkingSeconds()
        {
            return _GetWorkingSeconds(_workerId);
        }

    }
}
