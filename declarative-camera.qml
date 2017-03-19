import QtQuick 2.0
import QtMultimedia 5.4

Rectangle {
  id : cameraUI

  width: 1024
  height: 768

  color: "black"
  state: "PhotoCapture"

  states: [
    State {
      name: "PhotoCapture"
      StateChangeScript {
        script: {
          camera.captureMode = Camera.CaptureStillImage
          camera.start()
        }
      }
    },
    State {
      name: "PhotoPreview"
    }
  ]

  Camera {
    id: camera
    captureMode: Camera.CaptureStillImage

    imageCapture {
      onImageCaptured: {
        photoPreview.source = preview
        stillControls.previewAvailable = true
        cameraUI.state = "PhotoPreview"
      }
      onImageSaved: {
            console.log("output: " + camera.imageCapture.capturedImagePath)
            backend.postMessage("dongkechang");
      }
    }

    videoRecorder {
      resolution: "640x480"
      frameRate: 30
    }
  }

  PhotoPreview {
    id : photoPreview
    anchors.fill : parent
    onClosed: cameraUI.state = "PhotoCapture"
    visible: cameraUI.state == "PhotoPreview"
    focus: visible
  }

  VideoOutput {
    id: viewfinder
    visible: cameraUI.state == "PhotoCapture"

    x: 0
    y: 0
    width: parent.width - stillControls.buttonsPanelWidth
    height: parent.height

    source: camera
    autoOrientation: true
  }

  PhotoCaptureControls {
    id: stillControls
    anchors.fill: parent
    camera: camera
    visible: cameraUI.state == "PhotoCapture"
    onPreviewSelected: cameraUI.state = "PhotoPreview"
  }
}
