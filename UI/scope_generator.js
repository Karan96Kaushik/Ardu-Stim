var teeth, depth, radius;

function arcToRad(num) {
  return (360 / num) * (Math.PI / 180) / 2;
}

function draw_crank_scope(toothPattern, depth, radius, width, line, halfspeed) {
  var canvas = document.getElementById('crank');
  var c = canvas.getContext('2d');

  c.clearRect(0, 0, canvas.width, canvas.height);

  var x = canvas.width / 2;
  var y = canvas.height / 2
  var lastEnd = 0;
  var lastState = 0;
  var teeth = toothPattern.length / 2;
  //if(halfspeed) { teeth = teeth * 2; }
  var toothWidth;
  if(halfspeed) { toothWidth = (canvas.width / toothPattern.length); }
  else { toothWidth = (canvas.width / toothPattern.length); }

  console.log("Halfspeed is: " + halfspeed);

  c.beginPath();
  
  for (var i = 0; i < toothPattern.length; i++) {
    var newEnd;
    
    newEnd = lastEnd + toothWidth;

    if (toothPattern[i] == 1 || toothPattern[i] == 3 || toothPattern[i] == 5 || toothPattern[i] == 7 || toothPattern[i] == 9 || toothPattern[i] == 0xb || toothPattern[i] == 0xd || toothPattern[i] == 0xf) 
    {
      if(lastState == 0) { c.lineTo(newEnd, depth); }
      c.lineTo(newEnd, 0);
      lastState = 1;
      
    } else if (toothPattern[i] == 0 || toothPattern[i] == 2 || toothPattern[i] == 4 || toothPattern[i] == 6 || toothPattern[i] == 8 || toothPattern[i] == 0xa || toothPattern[i] == 0xc || toothPattern[i] == 0xe) 
    {
      if(lastState == 1) { c.lineTo(newEnd, 0); }
      c.lineTo(newEnd, depth);
      lastState = 0;
    }
    lastEnd = newEnd;
  }
  
  c.strokeStyle = '#ffff00';
  c.lineWidth = line;
  c.stroke();
}

function draw_cam_scope(toothPattern, depth, radius, width, line) {
  var canvas = document.getElementById('cam');
  var c = canvas.getContext('2d');

  c.clearRect(0, 0, canvas.width, canvas.height);

  var x = canvas.width / 2;
  var y = canvas.height / 2
  var lastEnd = 0;
  var lastState = 0;
  var teeth = toothPattern.length * 2;
  //if(halfspeed) { teeth = teeth * 2; }
  var toothWidth = (canvas.width / teeth) * 2;

  //depth = (radius / 100) * depth;

  c.beginPath();
  
  for (var i = 0; i <= (teeth * 2)-1; i++) {
    var newEnd;
    
    newEnd = lastEnd + toothWidth;

    if (toothPattern[i] == 2 || toothPattern[i] == 3 || toothPattern[i] == 6 || toothPattern[i] == 7 || toothPattern[i] == 0xb || toothPattern[i] == 0xa || toothPattern[i] == 0xf || toothPattern[i] == 0xe) 
    {
      if(lastState == 0) { c.lineTo(newEnd, depth); }
      c.lineTo(newEnd, 0);
      lastState = 1;
    } else if (toothPattern[i] == 0 || toothPattern[i] == 1 || toothPattern[i] == 4 || toothPattern[i] == 5 || toothPattern[i] == 8 || toothPattern[i] == 9 || toothPattern[i] == 0xc || toothPattern[i] == 0xd) 
    {
      if(lastState == 1) { c.lineTo(newEnd, 0); }
      c.lineTo(newEnd, depth);
      lastState = 0;
    }
    lastEnd = newEnd;
  }
  
  c.strokeStyle = '#0000FF';
  c.lineWidth = line;
  c.stroke();
}


function draw_third_scope(toothPattern, depth, radius, width, line) {
  var canvas = document.getElementById('third');
  var c = canvas.getContext('2d');

  c.clearRect(0, 0, canvas.width, canvas.height);

  console.log("TP:", toothPattern)
  var x = canvas.width / 2;
  var y = canvas.height / 2
  var lastEnd = 0;
  var lastState = 0;
  var teeth = toothPattern.length * 2;
  //if(halfspeed) { teeth = teeth * 2; }
  var toothWidth = (canvas.width / teeth) * 2;

  //depth = (radius / 100) * depth;

  c.beginPath();
  
  for (var i = 0; i <= (teeth * 2)-1; i++) {
    var newEnd;
    
    newEnd = lastEnd + toothWidth;

    if (toothPattern[i] == 4 || toothPattern[i] == 5 || toothPattern[i] == 6 || toothPattern[i] == 7 || toothPattern[i] == 0xf || toothPattern[i] == 0xe || toothPattern[i] == 0xc || toothPattern[i] == 0xd) 
    {
      if(lastState == 0) { c.lineTo(newEnd, depth); }
      c.lineTo(newEnd, 0);
      lastState = 1;
    } else if (toothPattern[i] == 0 || toothPattern[i] == 1 || toothPattern[i] == 2 || toothPattern[i] == 3 || toothPattern[i] == 8 || toothPattern[i] == 9 || toothPattern[i] == 0xa || toothPattern[i] == 0xb) 
    {
      if(lastState == 1) { c.lineTo(newEnd, 0); }
      c.lineTo(newEnd, depth);
      lastState = 0;
    }
    lastEnd = newEnd;
  }
  
  c.strokeStyle = '#00ff00';
  c.lineWidth = line;
  c.stroke();
}
