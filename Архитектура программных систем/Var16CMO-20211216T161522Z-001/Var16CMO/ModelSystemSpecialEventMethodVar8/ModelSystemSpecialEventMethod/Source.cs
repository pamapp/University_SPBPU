using System;

namespace ModelSystemSpecialEventMethod
{
    class Source
    {
        public Request sourceRequests { get; set; }
        public int numberSource { get; set; }
        public int serialNumber { get; set; } = 0;

        public Source(int numberSource, int serialNumber)
        {
            this.numberSource = numberSource;
            this.serialNumber = serialNumber;

            // random first request
            sourceRequests = new Request(Program.time + ((float)Program.random.NextDouble())/100, numberSource, serialNumber);
            serialNumber++;
        }

        public Source() { }

        public float GetTimeRequest()
        {
            if (sourceRequests == null) return -1;
            return sourceRequests.dateTime;
        }

        public Request GetNewRequest() // отдаём текущую сгенирированную и генерируем новую
        {
            Request temp = this.sourceRequests;
            float prevTime = temp.dateTime;

            serialNumber++;
            sourceRequests = null;
            // генерировать следующую заявку источника           
            sourceRequests = new Request(prevTime + Program.timeOfSourceGenerateNewRequest, numberSource, serialNumber);

            Program.numberOfRequestsWereGenerated++;

            if (Program.numberOfRequestsWereGenerated >= Program.totalRequestGenerate)
            {
                sourceRequests = null; 
                // больше не генерируем
            }

            Program.allRequestInSystem.Add(temp);
            // возращаем текущую
            return temp;
        }

    }
}
