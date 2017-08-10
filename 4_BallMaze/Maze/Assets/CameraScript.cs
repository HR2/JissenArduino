using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraScript : MonoBehaviour
{
 Camera camera;
 GameObject ball;
 public Vector3 viewPoint = new Vector3( 0.0f, 1.0f, -0.5f ); 

 void Start ()
 {
	
	camera = Camera.main;
	ball = GameObject.Find ("Sphere");
 }

 void Update ()
 {
	Vector3 cameraPos = new Vector3(
	 ball.transform.position.x,
	 ball.transform.position.y + viewPoint.y,
	 ball.transform.position.z + viewPoint.z);
	camera.transform.position = cameraPos;
	camera.transform.LookAt( ball.transform.position );
 }
}
