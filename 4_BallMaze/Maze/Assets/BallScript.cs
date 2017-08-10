using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BallScript : MonoBehaviour
{
 Vector3 defPos;

 void Start ()
 {
	defPos = gameObject.transform.position;
 }
	
 void Update ()
 {
	if (Input.GetKeyDown (KeyCode.Space))
	{
	 gameObject.transform.position = defPos;//初期位置に戻す
	 gameObject.GetComponent<Rigidbody>().velocity = Vector3.zero;//速度を0にする
	}
 }
}
