#ifndef OTA_HTML_H
#define OTA_HTML_H

#include <pgmspace.h>

const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="utf-8" />
  <meta
    name="viewport"
    content="width=device-width, initial-scale=1, viewport-fit=cover"
  />
  <title>Custom OTA Update</title>
  <style>
    /* Color system (5 total):
       - Primary: Blue (#2563eb)
       - Neutrals: Background #0b1220, Card #0f172a, Text #ffffff
       - Accent: Amber (#f59e0b)
    */

    :root{
      --bg: #0b1220;
      --card: #0f172a;
      --text: #ffffff;
      --muted: rgba(255,255,255,0.7);
      --border: rgba(255,255,255,0.08);
      --primary: #2563eb;
      --primary-600: #1d4ed8;
      --primary-700: #1e40af;
      --accent: #f59e0b;
      --shadow: 0 10px 30px rgba(0,0,0,0.35), 0 4px 10px rgba(0,0,0,0.25);
      --radius-lg: 16px;
      --radius-md: 10px;
      --radius-sm: 8px;
      --focus: 0 0 0 3px rgba(37, 99, 235, 0.4);
    }

    * { box-sizing: border-box; }
    html, body { height: 100%; }
    body{
      margin: 0;
      font-family: ui-sans-serif, system-ui, -apple-system, Segoe UI, Roboto, Helvetica, Arial, "Apple Color Emoji", "Segoe UI Emoji";
      background: var(--bg);
      color: var(--text);
      display: grid;
      place-items: center;
      padding: 24px;
    }

    /* Page container */
    .shell{
      width: 100%;
      max-width: 720px;
      display: grid;
      gap: 16px;
      justify-items: center;
    }

    /* Header */
    .brand{
      display: flex;
      align-items: center;
      gap: 12px;
      color: var(--muted);
      font-size: 14px;
      letter-spacing: .08em;
      text-transform: uppercase;
    }

    .card{
      position: relative;
      width: 100%;
      background: var(--card);
      border: 1px solid var(--border);
      border-radius: var(--radius-lg);
      padding: 24px;
      box-shadow: var(--shadow);
      overflow: hidden;
      transform: translateZ(0);
      animation: cardFloat 10s ease-in-out infinite;
    }

    /* Animated accent sweep (subtle) */
    .card::before{
      content: "";
      position: absolute;
      top: 0;
      left: -40%;
      width: 40%;
      height: 3px;
      background: var(--accent);
      opacity: .9;
      border-bottom-right-radius: 3px;
      border-top-right-radius: 3px;
      animation: sweep 4s linear infinite;
      will-change: transform;
    }

    @keyframes sweep{
      0% { transform: translateX(0%); }
      100% { transform: translateX(350%); }
    }

    @keyframes cardFloat{
      0%, 100% { transform: translateY(0); }
      50% { transform: translateY(-6px); }
    }

    h1{
      margin: 0 0 8px;
      font-size: 22px;
      line-height: 1.3;
      letter-spacing: -0.02em;
    }

    p.lead{
      margin: 0 0 20px;
      color: var(--muted);
      font-size: 14px;
      line-height: 1.6;
    }

    /* Dropzone */
    .dropzone {
      display: grid;
      gap: 16px;
      width: 100%;
      padding: 32px;
      border: 2px dashed var(--border);
      border-radius: var(--radius-md);
      place-items: center;
      text-align: center;
      transition: background 0.2s, border-color 0.2s;
    }

    .dropzone-hover {
      background: rgba(255,255,255,0.05);
      border-color: rgba(255,255,255,0.2);
    }
    
    .dropzone-label {
      font-size: 16px;
      color: var(--muted);
      display: flex;
      flex-direction: column;
      align-items: center;
      gap: 8px;
    }

    .dropzone-text {
      font-size: 14px;
    }
    
    .dropzone-text span {
      display: block;
      color: var(--primary);
    }

    /* File input is hidden */
    .file-input {
      display: none;
    }

    /* The file name display */
    .file-name {
      font-size: 14px;
      font-weight: 500;
      color: var(--muted);
      margin-top: 10px;
    }
    
    /* Progress bar */
    .progress-bar {
      width: 100%;
      height: 8px;
      background: var(--border);
      border-radius: 9999px;
      overflow: hidden;
      margin-top: 16px;
      opacity: 0;
      transition: opacity 0.3s;
    }

    .progress-bar-fill {
      height: 100%;
      width: 0%;
      background: var(--accent);
      transition: width 0.2s ease-out;
    }

    .progress-active {
      opacity: 1;
    }

    /* Buttons */
    .btn {
      display: inline-flex;
      align-items: center;
      justify-content: center;
      padding: 12px 24px;
      border: 0;
      border-radius: var(--radius-sm);
      font-size: 14px;
      font-weight: 600;
      cursor: pointer;
      text-transform: uppercase;
      letter-spacing: .05em;
      transition: all 0.2s;
    }

    .btn-primary {
      background: var(--primary);
      color: var(--text);
    }

    .btn-primary:hover {
      background: var(--primary-600);
      transform: translateY(-2px);
      box-shadow: 0 4px 8px rgba(37,99,235,0.2);
    }

    /* Status messages */
    .status-message {
      margin-top: 16px;
      font-size: 14px;
      font-weight: 500;
    }
    
    .status-message.success {
      color: #34d399; /* green-400 */
    }

    .status-message.error {
      color: #f87171; /* red-400 */
    }

    .status-message.info {
      color: #60a5fa; /* blue-400 */
    }

    .controls {
      display: flex;
      gap: 12px;
    }

    .controls-group {
      display: flex;
      gap: 12px;
      align-items: center;
    }

    .controls-label {
      font-size: 14px;
      color: var(--muted);
      font-weight: 600;
      letter-spacing: .02em;
      text-transform: uppercase;
    }
    
    .switch {
      position: relative;
      display: inline-block;
      width: 48px;
      height: 24px;
    }

    .switch input {
      opacity: 0;
      width: 0;
      height: 0;
    }

    .slider {
      position: absolute;
      cursor: pointer;
      top: 0;
      left: 0;
      right: 0;
      bottom: 0;
      background-color: var(--border);
      transition: 0.4s;
      border-radius: 9999px;
    }

    .slider:before {
      position: absolute;
      content: "";
      height: 16px;
      width: 16px;
      left: 4px;
      bottom: 4px;
      background-color: var(--muted);
      transition: 0.4s;
      border-radius: 50%;
    }

    input:checked + .slider {
      background-color: var(--primary-600);
    }

    input:checked + .slider:before {
      transform: translateX(24px);
      background-color: var(--text);
    }

  </style>
</head>
<body>

  <div class="shell">
    <div class="brand">
      <svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="M12 2L2 7l10 5 10-5-10-5zM2 17l10 5 10-5M2 12l10 5 10-5"/></svg>
      ESP WebFlasher
    </div>

    <div class="card">
      <h1>Firmware Update</h1>
      <p class="lead">Select a firmware file (.bin) to upload. The device will reboot automatically after a successful update.</p>

      <form id="upload-form" method="POST" action="/update" enctype="multipart/form-data">
        <label for="file-input" class="dropzone" id="drop-zone">
          <input type="file" id="file-input" class="file-input" name="firmware" accept=".bin">
          <div class="dropzone-label">
            <svg xmlns="http://www.w3.org/2000/svg" width="32" height="32" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" class="w-8 h-8 opacity-70"><path d="M4 14.899A7 7 0 1 1 15.71 8h1.79a4.5 4.5 0 0 1 2.5 8.242M12 20v-8M8 16l4-4 4 4"/></svg>
            <div class="dropzone-text">
              <span>Drag & drop or click to select file</span>
              <p>Firmware file (.bin)</p>
            </div>
          </div>
        </label>
        
        <div class="progress-bar" id="progress-bar">
          <div class="progress-bar-fill" id="progress-fill"></div>
        </div>
        
        <div class="file-name" id="file-name-display">No file selected</div>
        <p class="status-message" id="status-message"></p>
        
        <div class="controls">
          <button type="submit" class="btn btn-primary" id="upload-btn">Upload</button>
        </div>
      </form>
    </div>

    <!-- Additional card for a control (optional) -->
    <div class="card">
      <h1>Device Control</h1>
      <p class="lead">Toggle the onboard LED to test the device.</p>
      <div class="controls-group">
        <span class="controls-label">Onboard LED</span>
        <label class="switch">
          <input type="checkbox" id="led-switch">
          <span class="slider"></span>
        </label>
      </div>
    </div>
  </div>

<script>
  // DOM Elements
  const dropZone = document.getElementById('drop-zone');
  const fileInput = document.getElementById('file-input');
  const fileNameDisplay = document.getElementById('file-name-display');
  const uploadForm = document.getElementById('upload-form');
  const progressBar = document.getElementById('progress-bar');
  const progressFill = document.getElementById('progress-fill');
  const statusMessage = document.getElementById('status-message');
  const uploadBtn = document.getElementById('upload-btn');
  const ledSwitch = document.getElementById('led-switch');

  // Drag and drop event listeners
  ['dragenter', 'dragover', 'dragleave', 'drop'].forEach(eventName => {
    dropZone.addEventListener(eventName, preventDefaults, false);
    document.body.addEventListener(eventName, preventDefaults, false);
  });

  ['dragenter', 'dragover'].forEach(eventName => {
    dropZone.addEventListener(eventName, () => dropZone.classList.add('dropzone-hover'), false);
  });

  ['dragleave', 'drop'].forEach(eventName => {
    dropZone.addEventListener(eventName, () => dropZone.classList.remove('dropzone-hover'), false);
  });

  dropZone.addEventListener('drop', handleDrop, false);

  function preventDefaults(e) {
    e.preventDefault();
    e.stopPropagation();
  }

  function handleDrop(e) {
    const dt = e.dataTransfer;
    const file = dt.files[0];
    fileInput.files = dt.files;
    fileNameDisplay.textContent = file.name;
    fileNameDisplay.style.color = 'var(--text)';
  }

  // File input change listener
  fileInput.addEventListener('change', () => {
    if (fileInput.files.length > 0) {
      fileNameDisplay.textContent = fileInput.files[0].name;
      fileNameDisplay.style.color = 'var(--text)';
    }
  });

  // Form submission handler
  uploadForm.addEventListener('submit', function(e) {
    e.preventDefault();
    
    if (fileInput.files.length === 0) {
      statusMessage.textContent = "Please select a file first.";
      statusMessage.className = "status-message error";
      return;
    }

    const file = fileInput.files[0];
    const formData = new FormData();
    formData.append('firmware', file, file.name);

    // Show progress bar
    progressBar.classList.add('progress-active');
    progressFill.style.width = '0%';
    statusMessage.textContent = "Uploading...";
    statusMessage.className = "status-message info";
    uploadBtn.disabled = true;

    // Use XMLHttpRequest for progress tracking
    const xhr = new XMLHttpRequest();
    xhr.open('POST', '/update', true);

    xhr.upload.addEventListener('progress', function(e) {
      if (e.lengthComputable) {
        const percentComplete = (e.loaded / e.total) * 100;
        progressFill.style.width = percentComplete.toFixed(2) + '%';
      }
    }, false);

    xhr.onload = function() {
      if (xhr.status === 200) {
        statusMessage.textContent = "Firmware updated successfully! Rebooting...";
        statusMessage.className = "status-message success";
        setTimeout(() => {
          window.location.reload();
        }, 5000);
      } else {
        statusMessage.textContent = `Error: ${xhr.statusText}`;
        statusMessage.className = "status-message error";
      }
      uploadBtn.disabled = false;
      progressBar.classList.remove('progress-active');
    };

    xhr.onerror = function() {
      statusMessage.textContent = "Upload failed. Please try again.";
      statusMessage.className = "status-message error";
      uploadBtn.disabled = false;
      progressBar.classList.remove('progress-active');
    };

    xhr.send(formData);
  });

  // LED control
  ledSwitch.addEventListener('change', async () => {
    const state = ledSwitch.checked ? 'on' : 'off';
    const url = `/led/${state}`;
    try {
      const response = await fetch(url);
      if (response.ok) {
        console.log(`LED is now ${state}`);
      } else {
        console.error('Failed to toggle LED');
      }
    } catch (error) {
      console.error('Network error:', error);
    }
  });
</script>

</body>
</html>
)=====";

#endif
