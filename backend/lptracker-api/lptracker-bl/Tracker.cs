using lptracker_bl.Models;
using System.IO.Ports;

namespace lptracker_bl;

public class Tracker : ITracker
{
    private static SerialPort? _serialPort;
    private const int BAUD_RATE = 9600;
    private Dictionary<string, Anchor> _anchors = new();

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
            _serialPort.WriteLine(msg);
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

    public void ReceiveTest(string msg)
    {
        Console.WriteLine($"< {msg}");
        HandleMsg(msg);
    }

    public void OnRecive(object sender, SerialDataReceivedEventArgs e)
    {
        /*
         
             №  latitude    longitude   altitude    db 
         anc~01_12.12345678_23.12345678_34.12345678_-50~02_12.345678_23.456789_34.567890_777~03_12.345678_23.456789_34.567890_777
         
             UWB latitude longitude altitude db  GPS latitude longitude altitude db
         pos;u:12.345678;23.456789;34.567890;-50|g:12.345678;23.456789;34.567890;777

         */
        var receivedData = _serialPort!.ReadLine();
        Console.WriteLine($"< {receivedData}");
        HandleMsg(receivedData);
    }

    public IReadOnlyList<Anchor> GetAnchors()
    {
        return _anchors.Values.ToList();
    }

    private void HandleMsg(string msg)
    {
        if (msg.StartsWith("anc~"))
            HandleAnchors(msg[4..]);
        else if (msg.StartsWith("pos~"))
            HandlePosition(msg[4..]);
        else
            Console.WriteLine("UNDEFINDE msg");
    }

    private void HandleAnchors(string msg)
    {
        var anchors = msg.Split('~');
        foreach (var a in anchors)
        {
            var anchor = new Anchor();
            var p = a.Split('_');
            anchor.Name = p[0];
            anchor.Latitude = double.Parse(p[1]);
            anchor.Longitude = double.Parse(p[2]);
            anchor.Altitude = double.Parse(p[3]);
            anchor.SignalLevel = int.Parse(p[4]);
            if (_anchors.TryGetValue(anchor.Name, out var existAnchor))
            {
                if (anchor.SignalLevel > existAnchor.SignalLevel)
                    _anchors[existAnchor.Name] = anchor;
            }
            else
            {
                _anchors[anchor.Name] = anchor;
            }
        }
    }

    private void HandlePosition(ReadOnlySpan<char> msg)
    {

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
