using System.Collections.Generic;
using System.Linq;

namespace ModelSystemSpecialEventMethod
{
    class Buffer
    {
        public Request[] buffer;
        public int bufferSize { get; set; } = 5;

        public int amountOfFailure { get; set; } = 0; // количество отказов
        public Buffer(int Size)
        {
            this.buffer = new Request[Size]; // FIFO
            bufferSize = Size;
        }

        public int Count { get; set; } = 0;

        int pointer { get; set; } = 0;

        public void AddToBuffer(Request request)
        {

            for (int i = pointer; i < bufferSize; i++)
            {
                if (buffer[i] == null)
                {
                    buffer[i] = request;
                    Program.state = "Заявка помещана в буфер: " + buffer[i].uniqueID;
                    
                    Count++;
                    pointer = i;
                    return;
                }
            }

            for (int j = 0; j < pointer; j++)
            {
                if (buffer[j] == null)
                {
                    buffer[j] = request;
                    Program.state = "Заявка помещана в буфер:" + buffer[j].uniqueID;
                    
                    Count++;
                    pointer = j;
                    return;
                }
            }

            float minTime = float.MaxValue;
            int minTimeIndex = -1;
            for (int i = 0; i < bufferSize; i++)
            {
                if (buffer[i] != null)
                {
                    if (buffer[i].dateTime < minTime)
                    {
                        minTime = buffer[i].dateTime;
                        minTimeIndex = i;

                    }
                }
            }
            

            buffer[minTimeIndex].EndTime = Program.time;
            Program.EndRequests.Add(buffer[minTimeIndex]);

            Program.state = "В заявке отказано: " + buffer[pointer].uniqueID;
            
            buffer[minTimeIndex] = null;
            buffer[minTimeIndex] = request;

            amountOfFailure++;

            return;
        }


        public Request takeFromBuffer(float currentTime) 
        {
            // LIFO
            // берём заявку под указателем т.к она пришла последняя

            if (this.Count == 0) // буфер пуст
            {
                return null;
            }

            Request tempReq = new Request();
            if (buffer[pointer] != null)
            {
                tempReq = buffer[pointer];
            }            
            buffer[pointer] = null;
            Program.state = "Заявка передана на прибор: " + tempReq.uniqueID;
            Count--;
            return tempReq;
        }
    }
}
