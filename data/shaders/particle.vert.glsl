attribute vec3 position;
attribute vec3 velocity;
attribute vec2 texTransform;
attribute float angVelocity;
attribute float birthTime;
attribute float pointSize;
uniform float time;
uniform vec3 acceleration;
varying float age;

varying mat2 texRot;
varying vec2 texTrans;

void main(void)
{
	age = time - birthTime;
	{
		float sin_theta = sin(age*angVelocity);
		float cos_theta = cos(age*angVelocity);
		texRot = mat2(cos_theta, -sin_theta, sin_theta, cos_theta);
		texTrans = texTransform;
	}
	vec3 pos = position + velocity*age + 0.5*acceleration*age*age;
	// Uniform accel. s = s0 + u t + 1/2 a t squared
#ifdef ZHACK
	logarithmicTransform(gl_ModelViewProjectionMatrix * vec4(pos, 1.0));
#else
	gl_Position = gl_ModelViewProjectionMatrix * pos;
#endif
	gl_PointSize = pointSize / gl_Position.z;
}

