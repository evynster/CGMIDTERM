#include "Transform.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>


const glm::mat4& Transform::rotate(const glm::vec3& rotateOn, const float rotationAngle) {

	return _rotateMat = glm::rotate(_rotateMat, glm::radians(rotationAngle), rotateOn);
}

const glm::mat4& Transform::rotate(const glm::vec3& eulerRotation) {
	return _rotateMat = glm::mat4_cast(glm::quat(glm::radians(eulerRotation)));
}

const glm::mat4& Transform::scale(const glm::vec3& scaleVec, const float sizeScalar) {
	return _scaleMat = glm::scale(_scaleMat, scaleVec * sizeScalar);
}

glm::vec3 Transform::translate(const glm::vec3& translateBy) {
	_translateMat = glm::translate(_translateMat, translateBy);
	return _translateMat[3];
}


void Transform::update() {
	_transformMat = _translateMat * _rotateMat * _scaleMat;

	if (_parent != NULL) {
		if (_parent->_worldTransformMat != glm::mat4{ 1.0f }) {
			_worldTransformMat = _parent->_worldTransformMat * _transformMat;
		}
	}
	else {
		_worldTransformMat = _transformMat;
	}
}