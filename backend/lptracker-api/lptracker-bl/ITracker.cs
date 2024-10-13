using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lptracker_bl;

public interface ITracker
{
    void Open(string portName);
    void Send(string msg);
    void Close();
}
