using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Uniduino;

public class AccScript : MonoBehaviour
{
 public Arduino arduino;

 int xPin = 0;
 int yPin = 1;
 int zPin = 2;

 List<Vector3> rotBuffer = new List<Vector3> ();
 public Vector3 baseValue = new Vector3( 535, 570, 445 );
 public int bufferNum = 1;

 void Start ()
 {
	arduino = Arduino.global;
	arduino.Setup (ConfigurePins);
 }

 void Update ()
 {
	int x = arduino.analogRead (xPin);
	int y = arduino.analogRead (yPin);
	int z = arduino.analogRead (zPin);
	Debug.Log ("X:" + x + "  Y:" + y + "  Z:" + z );

	Vector3 rawValue = new Vector3 (x, y, z);
	if (rawValue == Vector3.zero) {
	 rawValue = baseValue;
	}
	Vector3 adjValue = rawValue - baseValue;
	Vector3 newRotation = new Vector3 (Mathf.Atan2 (adjValue.x, adjValue.z) / Mathf.PI * 180, 0, Mathf.Atan2 (adjValue.y, adjValue.z) / Mathf.PI * 180);

	rotBuffer.Add (newRotation);
	if (rotBuffer.Count > bufferNum) {
	 rotBuffer.RemoveAt (0);
	}

	Vector3 rotSum = Vector3.zero;
	foreach (Vector3 rot in rotBuffer) {
	 rotSum += rot;
	}
	Vector3 rotAverage = rotSum / rotBuffer.Count;

	gameObject.transform.rotation = Quaternion.Euler (rotAverage);
 }

 void ConfigurePins ()
 {
	arduino.pinMode (xPin, PinMode.ANALOG);
	arduino.pinMode (yPin, PinMode.ANALOG);
	arduino.pinMode (zPin, PinMode.ANALOG);
	arduino.reportAnalog (xPin, 1);
	arduino.reportAnalog (yPin, 1);
	arduino.reportAnalog (zPin, 1);
 }
}
