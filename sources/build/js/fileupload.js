const progressBar = document.getElementById('progressOfUpload');
const button = document.getElementById('uploadButton');
const progressInformation = document.getElementById("progressInformation");
const xhr = new XMLHttpRequest();

button.addEventListener('click', executeUpload);

xhr.onload=function(evt){
        
    alert(xhr.responseText);
}

xhr.onerror=function(){
    alert('アップロード失敗しました...\n');
}

xhr.upload.onprogress=function(evt){
    let progVal = (evt.loaded / evt.total * 100).toFixed(1);
    progressBar.value = progVal;
    progressInformation.innerHTML = progVal + '%';
}

function executeUpload(evt)
{
    const chosenFile = document.getElementById('chooseFile').files[0];
    let formData = new FormData();
    formData.append( "file", chosenFile );
   
    xhr.open('POST', 'upload', true);
    xhr.send(formData);
};
