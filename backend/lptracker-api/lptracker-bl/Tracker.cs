using System.IO.Ports;

namespace lptracker_bl;

public class Tracker : ITracker
{
    private static SerialPort? _serialPort;
    private const int BAUD_RATE = 9600;

    public void Open(string portName)
    {
        TryClose();
        _serialPort = new SerialPort(portName, BAUD_RATE)
        {
            DtrEnable = true
        };
        _serialPort.DataReceived += OnRecive;

        try
        {
            _serialPort.Open();
            Console.WriteLine($"{portName} port opened success");
        }
        catch (Exception ex)
        {
            Console.WriteLine("Error init: " + ex.Message);
            TryClose();
            throw;
        }
    }

    public async Task Send(string msg)
    {
        if (_serialPort is null)
        {
            Console.WriteLine("Need init!");
            return;
        }

        try
        {
            _serialPort.WriteLine(msg + "$");
            Console.WriteLine("Sent to Arduino: " + msg);
        }
        catch (Exception ex)
        {
            Console.WriteLine("Error send: " + ex.Message);
            throw;
        }
    }

    public void Close()
    {
        TryClose();
    }

    public void OnRecive(object sender, SerialDataReceivedEventArgs e)
    {
        var receivedData = _serialPort!.ReadLine();
        Console.WriteLine("Received from Arduino: " + receivedData);
    }

    private void TryClose()
    {
        if (_serialPort is null)
            return;

        try
        {
            _serialPort.DataReceived -= OnRecive;
            _serialPort.Close();
        }
        catch (Exception ex)
        {
            Console.WriteLine("Error close: " + ex.Message);
            throw;
        }
        finally
        {
            _serialPort = null;
        }
    }
}
