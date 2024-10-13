using lptracker_bl;
using Microsoft.AspNetCore.Mvc;

namespace lptracker_api;

public static class Endpoints
{
    private static ITracker _tracker;

    public static WebApplication AddLptrackerEndpoints(this WebApplication app, ITracker tracker)
    {
        _tracker = tracker;
        app.MapGet("/open", GetOpen).WithName(nameof(GetOpen)).WithOpenApi();
        app.MapGet("/send", Send).WithName(nameof(Send)).WithOpenApi();
        app.MapGet("/close", Close).WithName(nameof(Close)).WithOpenApi();

        return app;
    }

    private static async Task GetOpen([FromQuery] string portName)
    {
        _tracker.Open(portName);
    }

    private static async Task Send([FromQuery] string msg)
    {
        _tracker.Send(msg);
    }

    private static async Task Close()
    {
        _tracker.Close();
    }
}
