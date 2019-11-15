using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Memory;
using System.Diagnostics;
namespace AdCap_
{
    class Memory_managment
    {
        Mem m;
        int pid;
        public Memory_managment()
        {
            pid = Process.GetProcessesByName("adventure-capitalist")[0].Id;
            m = new Mem();
            m.OpenProcess(pid);
        }

        public void setStatus(string pointer, string type, string value)
        {
            m.writeMemory(pointer, type, value);
        }
        
    }
}
