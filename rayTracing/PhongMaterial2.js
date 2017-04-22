/* 
 * @requires Vector3
 * @requires Color
 */

PhongMaterial = function(diffuse, specular, shininess, reflectiveness) {
    this.diffuse = diffuse;
    this.specular = specular;
    this.shininess = shininess;
    this.reflectiveness = reflectiveness;
};

// global temp
var lightDir = new Vector3(1, 1, 1).normalize();
var lightColor = Color.white;

PhongMaterial.prototype = {
    sample: function(ray, position, normal) {
        var NdotL = normal.dot(lightDir);
        var H = (lightDir.subtract(ray.direction)).normalize();
		//var r = -2 * normal.dot(NdotL).add(lightDir);
		var R = normal.multiply(-2 * normal.dot(lightDir)).add(lightDir);
        var NdotH = normal.dot(H);
        var VdotR=ray.direction.dot(R);
		var diffuseTerm = this.diffuse.multiply(Math.max(NdotL, 0));
        //var specularTerm = this.specular.multiply(Math.pow(Math.max(NdotH, 0), this.shininess));
		var specularTerm = this.specular.multiply(Math.pow(Math.max(VdotR, 0), this.shininess));
        return lightColor.modulate(diffuseTerm.add(specularTerm));
    }
};
