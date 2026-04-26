import cv2
import numpy as np
from tensorflow.keras.models import load_model

# Load trained model
model = load_model("classifyWaste.h5")

# TrashNet classes
classes = [
    "cardboard",
    "glass",
    "metal",
    "paper",
    "plastic",
    "trash"
]

# Start webcam
cap = cv2.VideoCapture(0)

while True:
    ret, frame = cap.read()

    if not ret:
        break

    # Resize frame
    img = cv2.resize(frame, (224, 224))

    # Normalize
    img = img / 255.0

    # Expand dimensions
    img = np.expand_dims(img, axis=0)

    # Prediction
    prediction = model.predict(img)

    class_index = np.argmax(prediction)
    label = classes[class_index]
    confidence = round(np.max(prediction) * 100, 2)

    # Display result
    cv2.putText(
        frame,
        f"{label} ({confidence}%)",
        (20, 40),
        cv2.FONT_HERSHEY_SIMPLEX,
        1,
        (0, 255, 0),
        2
    )

    cv2.imshow("Smart Waste Detection", frame)

    # Quit on Q
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
