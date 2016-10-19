from flask import Flask, jsonify, abort, request
import os.path

app = Flask(__name__)

# Example : curl -i http://localhost:1010/api/LedState/2
# Returns { "ledstate" : 1 } if corresponding file exists
# otherwise { "ledstate" : 0 } is returned
@app.route('/api/LedState/<int:led_id>', methods=['GET'])
def get_led_state(led_id):

    # if a file in the current folder exists called led1, led2 etc
    # the current state of the corresponding led is regarded as on
    buttonState = 0;
    if (os.path.exists("led" + str(led_id))):
        buttonState = 1

    return jsonify({'ledstate': buttonState})

#
# Sets the count value for a button
# Example:
# curl -i -H "Content-Type: application/json" -X PUT -d '{"count":"3"}' http://localhost:1010/api/ButtonPressCount/2
# 
@app.route('/api/ButtonPressCount/<int:button_id>', methods=['PUT'])
def update_button_count(button_id):
    if not request.json:
        abort(400)
    if not 'count' in request.json:
        abort(400)

    # Get updated count value from the body of the PUT request
    count = request.json.get('count')

    print("Button " + str(button_id) + " has been pressed " + count + " times")

    return jsonify({'count': count})

if __name__ == "__main__":
    app.run(host='0.0.0.0',port=1010,debug=True)
