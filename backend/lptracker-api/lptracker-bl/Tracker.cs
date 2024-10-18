using lptracker_bl.Models;
using System.IO.Ports;

namespace lptracker_bl;

public class Tracker : ITracker
{
    private static SerialPort? _serialPort;
    private const int BAUD_RATE = 9600;
    private List<string> _logs = new();
    private Dictionary<string, Anchor> _anchors = new();
    private List<DronPosition> _uwbPosition = new();
    private List<DronPosition> _gpsPosition = new();

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
        _logs.Add(msg);
        Console.WriteLine($"< {msg}");
        HandleMsg(msg);
    }

    public void OnRecive(object sender, SerialDataReceivedEventArgs e)
    {
        /*
         
             №  latitude    longitude   altitude    db  time
         anc~01_12.12345678_23.12345678_34.12345678_-50_2024-01-01T16-28-12~02_12.345678_23.456789_34.567890_777_2024-01-01T16-28-12~03_12.345678_23.456789_34.567890_777_2024-01-01T16-28-12
         
             latitude  longitude altitude  db time               GPS 
         pos~12.345678_23.456789_34.567890_0_2024-01-01T16-28-12~12.345678_23.456789_34.567890_-777_2024-01-01T16-28-12
         pos~12.345678_23.456789_34.567890_0_2024-01-01T16-28-12

         */
        var receivedData = _serialPort!.ReadLine();
        Console.WriteLine($"< {receivedData}");
        HandleMsg(receivedData);
    }

    public IReadOnlyList<Anchor> GetAnchors()
    {
        return _anchors.Values
            .OrderBy(i => i.Name)
            .ToList();
    }

    public IReadOnlyList<string> GetLogs()
    {
        return _logs;
    }

    public IReadOnlyList<DronPosition> GetUwb()
    {
        return _uwbPosition;
    }

    public IReadOnlyList<DronPosition> GetGps()
    {
        return _gpsPosition;
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
            anchor.LastTime = p[5];
            if (_anchors.TryGetValue(anchor.Name, out var existAnchor))
            {
                if (anchor.SignalLevel >= existAnchor.SignalLevel)
                    _anchors[existAnchor.Name] = anchor;
            }
            else
            {
                _anchors[anchor.Name] = anchor;
            }
        }
    }

    private void HandlePosition(string msg)
    {
        var types = msg.Split('~');
        var p = types[0].Split('_');
        var uwb = new DronPosition
        {
            Latitude = double.Parse(p[0]),
            Longitude = double.Parse(p[1]),
            Altitude = double.Parse(p[2]),
            SignalLevel = int.Parse(p[3]),
            Time = p[4]
        };
        _uwbPosition.Add(uwb);
        if (types.Length == 1)
            return;
        p = types[1].Split('_');
        var gps = new DronPosition
        {
            Latitude = double.Parse(p[0]),
            Longitude = double.Parse(p[1]),
            Altitude = double.Parse(p[2]),
            SignalLevel = int.Parse(p[3]),
            Time = p[4]
        };
        _gpsPosition.Add(gps);
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
