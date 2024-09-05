using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace LevelEditor
{
    public static class GameEngineAPI
    {
        [DllImport("GameEngineCore.dll")] public static extern IntPtr Renderer_Windows_Renderer(ref uint pPropertyCount);
    }
}
