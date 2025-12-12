using System.Windows;

namespace PrimeFlux.Editor
{
    public partial class App : Application
    {
        protected override void OnStartup(StartupEventArgs e)
        {
            base.OnStartup(e);
            System.Console.WriteLine("[C# Editor] PrimeFlux Level Editor starting...");
        }
    }
}
