Drawable::Drawable(const std::string& sprite, Vector<float> size,
                   float rotation) {
  this->size = size;
  this->sprite = sprite;
  this->rotation = rotation;
}

const Vector<float>& Drawable::get_size() const { return size; }

const std::string& Drawable::get_sprite() const { return sprite; }

const float Drawable::get_rotation() const { return rotation; }

void Drawable::set_rotation(float amount) { rotation = amount; }
when