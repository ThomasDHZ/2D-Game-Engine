using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace LevelEditor
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            UInt32 extensionCount = 0;
            VkResult result = VulkanAPI.vkEnumerateInstanceExtensionProperties(IntPtr.Zero, ref extensionCount, IntPtr.Zero);

            if (result == VkResult.VK_SUCCESS)
            {
                Console.WriteLine($"Available Vulkan extensions: {extensionCount}");
            }
            else
            {
                Console.WriteLine($"Failed to enumerate extensions: {result}");
            }
        }
    }
}
