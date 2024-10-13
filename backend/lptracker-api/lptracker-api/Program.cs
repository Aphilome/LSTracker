using lptracker_api;
using lptracker_bl;

var builder = WebApplication.CreateBuilder(args);
builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen();

var app = builder.Build();
if (app.Environment.IsDevelopment())
{
    app.UseSwagger();
    app.UseSwaggerUI();
}

ITracker tracker = new Tracker();


app.AddLptrackerEndpoints(tracker);

app.Run();
