FROM python

WORKDIR /usr/src

COPY requirements.txt .

RUN pip install -r requirements.txt

RUN apt update && apt install -y unzip

RUN wget https://stockfish.s3.amazonaws.com/stockfish-9-linux.zip

RUN unzip stockfish-9-linux.zip

COPY . .

CMD ["python", "ai.py"]
