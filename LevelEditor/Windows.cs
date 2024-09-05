using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace LevelEditor
{
    public static class Windows
    {
        [DllImport("kernel32.dll", SetLastError = true)]
        private static extern IntPtr GetModuleHandle(string lpModuleName);

        public static IntPtr GetHINSTANCE()
        {
            string moduleName = Process.GetCurrentProcess().ProcessName + ".exe";

            IntPtr hInstance = GetModuleHandle(moduleName);

            if (hInstance == IntPtr.Zero)
            {
                int errorCode = Marshal.GetLastWin32Error();
                MessageBox.Show("Unable to get HINSTANCE. Error code: " + errorCode);
            }

            return hInstance;
        }
    }
}
