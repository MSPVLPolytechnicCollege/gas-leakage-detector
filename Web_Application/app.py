import serial.tools.list_ports
from flask import Flask, jsonify, render_template
from twilio.rest import Client


app=Flask(__name__)
ports = serial.tools.list_ports.comports()


@app.route('/')
def home():
    return render_template('index.html')


@app.route('/data')
def get_data():
    if ports:
        p = ports[0].device
        ser = serial.Serial(p, 115200, timeout=1)
        while True:
            if ser.in_waiting > 0:
                data = ser.readline().decode('utf-8', errors='ignore').strip()
                if int(data)>500:
                  account_sid = 'AC373075ae0c58d81c230f007a6cb35ee9'
                  auth_token = '6f915b93c946705089a4c138d38aadc9'
                  client = Client(account_sid, auth_token)

                  message = client.messages.create(
                    from_='+17753185612',
                    body='EMERGENCY ALERT ! Gas leakage detected in your home !',
                    to='+919385352239'
                  )
                  print(message.sid)


                return jsonify({"gas_level": data})



if __name__ == '__main__':
    app.run(debug=True)










