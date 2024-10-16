namespace lptracker_bl.Models;
 
public class Anchor
{
    public string Name { get; set; } = string.Empty;
    
    public double Latitude { get; set; }

    public double Longitude { get; set; }

    public double Altitude { get; set; }

    public int SignalLevel { get; set; }
}
