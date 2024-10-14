using lptracker_bl;
using Microsoft.AspNetCore.Mvc;

namespace lptracker_api;

public static class Endpoints
{
    public static WebApplication AddLptrackerEndpoints(this WebApplication app)
    {
        app.MapPost("/open", GetOpen).WithName(nameof(GetOpen)).WithOpenApi();
        app.MapPut("/send", Send).WithName(nameof(Send)).WithOpenApi();
        app.MapDelete("/close", Close).WithName(nameof(Close)).WithOpenApi();

        return app;
    }

    private static async Task GetOpen([FromQuery] string portName, ITracker tracker)
    {
        tracker.Open(portName);
    }

    private static async Task Send([FromQuery] string msg, ITracker tracker)
    {
        await tracker.Send(msg);
    }

    private static async Task Close(ITracker tracker)
    {
        tracker.Close();
    }
}
