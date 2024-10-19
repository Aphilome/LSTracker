namespace lptracker_bl.Models;

public class DronPosition
{
    public double Latitude { get; set; }

    public double Longitude { get; set; }

    public double Altitude { get; set; }

    public int? SignalLevel { get; set; }

    public string Time { get; set; } = string.Empty;
}
