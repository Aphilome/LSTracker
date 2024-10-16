using lptracker_bl.Models;

namespace lptracker_bl;

public interface ITracker
{
    void Open(string portName);
    Task Send(string msg);
    void Close();
    void ReceiveTest(string msg);
    IReadOnlyList<Anchor> GetAnchors();
}
