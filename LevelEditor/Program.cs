using System;
using System.Runtime.InteropServices;

public enum VkResult
{
    VK_SUCCESS = 0,
    // Add other Vulkan result codes as needed
}

class Program
{

    // Import the function from your DLL
    [DllImport("GameEngineCore.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern int SimpleTest();
    [DllImport("GameEngineCore.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode)]
    public static extern IntPtr CreateVulkanWindow(IntPtr hInstance, int width, int height, [MarshalAs(UnmanagedType.LPWStr)] string title);

    static void Main(string[] args)
    {
        int result = SimpleTest();
        IntPtr hInstance = IntPtr.Zero; // Replace this with the actual instance
        int width = 800;   // Example window width
        int height = 600;  // Example window height
        string title = "My Vulkan Window"; // Example window title

        // Call the function
        IntPtr windowHandle = CreateVulkanWindow(hInstance, width, height, title);

        // Check the returned window handle
        if (windowHandle == IntPtr.Zero)
        {
            Console.WriteLine("Failed to create Vulkan window.");
        }
        else
        {
            Console.WriteLine("Vulkan window created successfully!");
            // Here you can proceed with your application logic
        }

        // Prevent the console from closing immediately
        Console.ReadLine();
    }
}