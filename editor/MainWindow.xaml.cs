using System;
using System.Windows;
using Microsoft.Win32;

namespace PrimeFlux.Editor
{
    public partial class MainWindow : Window
    {
        private bool isConnectedToEngine = false;

        public MainWindow()
        {
            InitializeComponent();
            LogMessage("[Editor] PrimeFlux Level Editor initialized");
        }

        private void LogMessage(string message)
        {
            ConsoleOutput.Text += $"{message}\n";
            ConsoleOutput.ScrollToEnd();
        }

        private void NewScene_Click(object sender, RoutedEventArgs e)
        {
            LogMessage("[Editor] Creating new scene...");
            MessageBox.Show("New scene created (placeholder)", "New Scene", 
                MessageBoxButton.OK, MessageBoxImage.Information);
        }

        private void OpenScene_Click(object sender, RoutedEventArgs e)
        {
            var dialog = new OpenFileDialog
            {
                Filter = "Scene Files (*.scene)|*.scene|All Files (*.*)|*.*",
                Title = "Open Scene"
            };

            if (dialog.ShowDialog() == true)
            {
                LogMessage($"[Editor] Opening scene: {dialog.FileName}");
                // TODO: Load scene via Rust serialization
            }
        }

        private void SaveScene_Click(object sender, RoutedEventArgs e)
        {
            var dialog = new SaveFileDialog
            {
                Filter = "Scene Files (*.scene)|*.scene|All Files (*.*)|*.*",
                Title = "Save Scene"
            };

            if (dialog.ShowDialog() == true)
            {
                LogMessage($"[Editor] Saving scene: {dialog.FileName}");
                // TODO: Save scene via Rust serialization
            }
        }

        private void Exit_Click(object sender, RoutedEventArgs e)
        {
            Application.Current.Shutdown();
        }

        private void ConnectEngine_Click(object sender, RoutedEventArgs e)
        {
            if (!isConnectedToEngine)
            {
                LogMessage("[Editor] Connecting to engine via TCP...");
                // TODO: Implement TCP connection to C++ engine
                isConnectedToEngine = true;
                LogMessage("[Editor] Connected to engine (placeholder)");
            }
            else
            {
                LogMessage("[Editor] Already connected to engine");
            }
        }

        private void DisconnectEngine_Click(object sender, RoutedEventArgs e)
        {
            if (isConnectedToEngine)
            {
                LogMessage("[Editor] Disconnecting from engine...");
                isConnectedToEngine = false;
                LogMessage("[Editor] Disconnected");
            }
        }
    }
}
