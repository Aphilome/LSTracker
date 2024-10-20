﻿using lptracker_bl;
using lptracker_bl.Models;
using Microsoft.AspNetCore.Mvc;

namespace lptracker_api;

public static class Endpoints
{
    public static WebApplication AddLptrackerEndpoints(this WebApplication app)
    {
        app.MapPost("/open", GetOpen).WithName(nameof(GetOpen)).WithOpenApi();
        app.MapPut("/send", Send).WithName(nameof(Send)).WithOpenApi();
        app.MapDelete("/close", Close).WithName(nameof(Close)).WithOpenApi();
        app.MapGet("/receive-test", ReceiveTest).WithName(nameof(ReceiveTest)).WithOpenApi();
        app.MapGet("/anchors", GetAnchors).WithName(nameof(GetAnchors)).WithOpenApi();
        app.MapGet("/logs", GetLogs).WithName(nameof(GetLogs)).WithOpenApi();
        app.MapGet("/gps", GetGps).WithName(nameof(GetGps)).WithOpenApi();
        app.MapGet("/uwb", GetUwb).WithName(nameof(GetUwb)).WithOpenApi();

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

    private static async Task ReceiveTest([FromQuery] string msg, ITracker tracker)
    {
        tracker.ReceiveTest(msg);
    }

    private static async Task<IReadOnlyList<Anchor>> GetAnchors(ITracker tracker)
    {
        return tracker.GetAnchors();
    }

    private static async Task<IReadOnlyList<string>> GetLogs(ITracker tracker)
    {
        return tracker.GetLogs();
    }

    private static async Task<IReadOnlyList<DronPosition>> GetUwb(ITracker tracker)
    {
        return tracker.GetUwb();
    }

    private static async Task<IReadOnlyList<DronPosition>> GetGps(ITracker tracker)
    {
        return tracker.GetGps();
    }
}
