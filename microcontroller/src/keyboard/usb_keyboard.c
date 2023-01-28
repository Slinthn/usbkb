/**
 * @brief USB component of the keyboard
 * 
 */

/**
 * @brief Send single key press
 * 
 */
void usb_send_key(uint8_t key) {

  STS(UENUM) = USB_KEYBOARD_ENDPOINT;
  STS(UEDATX) = 0;
  STS(UEDATX) = 0;
  STS(UEDATX) = key;
  STS(UEDATX) = 0;
  STS(UEDATX) = 0;
  STS(UEDATX) = 0;
  STS(UEDATX) = 0;
  STS(UEDATX) = 0;
  STS(UEINTX) = 0b00111010;
}

/**
 * @brief Check whether a key is in the keylist
 * 
 */
uint8_t usb_check_key(uint8_t keylist[USB_HID_MAX_KEYS], uint8_t key) {

  for (uint8_t i = 0; i < USB_HID_MAX_KEYS; i++) {
    if (keylist[i] == key) {
      return i;
    }
  }
  
  return 0xFF;
}

/**
 * @brief Send USB_HID_MAX_KEYS key presses
 * 
 */
void usb_send_keys(uint8_t keylist[USB_HID_MAX_KEYS]) {

  STS(UENUM) = USB_KEYBOARD_ENDPOINT;
  STS(UEDATX) = 0;
  STS(UEDATX) = 0;
  for (uint8_t i = 0; i < USB_HID_MAX_KEYS; i++) {
    STS(UEDATX) = keylist[i];
  }
  STS(UEINTX) = 0b00111010;
}

/**
 * @brief Adds a key to the key list
 * 
 */
uint8_t usb_add_key(uint8_t keylist[USB_HID_MAX_KEYS], uint8_t key) {

  if (usb_check_key(keylist, key) != 0xFF) {
    return 0xFF;
  }

  for (uint8_t i = 0; i < USB_HID_MAX_KEYS; i++) {
    if (!keylist[i]) {
      keylist[i] = key;
      return i;
    }
  }

  return 0xFF;
}

/**
 * @brief Removes a key from the key list
 * 
 */
uint8_t usb_remove_key(uint8_t keylist[USB_HID_MAX_KEYS], uint8_t key) {

  uint8_t index = usb_check_key(keylist, key);
  if (index != 0xFF) {
    keylist[index] = 0;
  }

  return index;
}

/**
 * @brief Removes a key from the key list
 * 
 */
void usb_reset_keys(uint8_t keylist[USB_HID_MAX_KEYS]) {

  for (uint8_t i = 0; i < USB_HID_MAX_KEYS; i++) {
    keylist[i] = 0;
  }
}
