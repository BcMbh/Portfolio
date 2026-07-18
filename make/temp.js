
const SheetName = "TestData"; 
const cells ={
  Token: "B1",
  Current: "B2",
  Delete: "B3",
  Instant: "B6",
  Schedule: "B7",
  Recurring: "B8",
  Topic: "B11",
  Date: "B12",
  Duration: "B13",
  Password: "B14",
  Personal: "B5",
  Select: "B18",
  Daily: "E2",
  Weekly: "E3",
  Monthly: "E4",
  Interval: "E5",
  Occurance: "E6",
  EndDate: "E7",
  EndTimes: "E8",
  Monday: "E11",
  Tuesday: "E12",
  Wednesday: "E13",
  Thursday: "E14",
  Friday: "E15",
  Saturday: "E16",
  Sunday: "E17",
  MonthDay: "E18",
};
// ---------------------

//Trigger
function onEdit(e){
  //Loop Prevention
  const lock = LockService.getScriptLock();
  if(!lock.tryLock(10000)){
    return;
  }

  try {
    const range = e.range;
    const sheet = range.getSheet();
    const meeting = range.getA1Notation();
    const newValue = e.value;

    if(sheet.getName()!== SheetName){
      return;
    }

    //Logic
    if(meeting === cells.Token){
      tokenEdit(sheet, newValue);
    }
    else if(meeting === cells.Current){
      getMeeting(sheet, newValue);
    }
    else if(meeting === cells.Delete){
      deleteMeeting(sheet, newValue);
    }
    else if(meeting === cells.Instant || meeting === cells.Schedule || meeting === cells.Recurring){
      meetingType(sheet, meeting, newValue);
      const currentMeetingId = sheet.getRange(cells.Current).getValue();
      if(!currentMeetingId && newValue === true) {
        createMeeting(sheet, meeting);
      }
    }
    else if(meeting === cells.Daily || meeting === cells.Weekly || meeting === cells.Monthly){
      recureType(sheet, meeting, newValue);
      editMeeting(sheet, meeting, newValue)
    }
    else if(
      meeting === cells.Topic || meeting === cells.Date || meeting === cells.Duration ||
      meeting === cells.Password || meeting === cells.Personal || meeting === cells.Select ||
      meeting === cells.Interval || meeting === cells.Occurance || meeting === cells.EndDate ||
      meeting === cells.EndTimes || meeting === cells.Monday || meeting === cells.Tuesday ||
      meeting === cells.Wednesday || meeting === cells.Thursday || meeting === cells.Friday ||
      meeting === cells.Saturday || meeting === cells.Sunday || meeting === cells.MonthDay
    ){editMeeting(sheet, meeting, newValue);}
    
  }catch(err){
    Logger.log(`onEdit Error: ${err.message} \nStack: ${err.stack}`);
  }finally{
    //Stop Loop Prevention
    lock.releaseLock();
  }
}


//Token
function tokenEdit(sheet, tokenValue){
  //status to C1.
  try{
    const user = zoomApi("/users/me", 'GET', null, tokenValue);
    sheet.getRange("C1").setValue(`Valid: ${user.email}`);
  }catch (err){
    sheet.getRange("C1").setValue("Invalid Token" + err.message);
  }
}

function meetingType(sheet, meeting, newValue){
  if(newValue === true){
    if(meeting === cells.Instant){
      sheet.getRange(cells.Schedule).setValue(false);
      sheet.getRange(cells.Recurring).setValue(false);
      
      clearCells(sheet, `${cells.Daily}:${cells.MonthDay}`, cells.EndDate);
      sheet.getRange(cells.Select).setValue("");
    }else if (meeting === cells.Schedule){
      sheet.getRange(cells.Instant).setValue(false);
      sheet.getRange(cells.Recurring).setValue(false);

      clearCells(sheet, `${cells.Daily}:${cells.MonthDay}`, cells.EndDate);
      sheet.getRange(cells.Select).setValue("");
    }else if (meeting === cells.Recurring){
      sheet.getRange(cells.Instant).setValue(false);
      sheet.getRange(cells.Schedule).setValue(false);

      getMeeting(sheet, meetingId); 
    }
  }
}

//---------------------Zoom-------------------------
//Helper Function
function zoomApi(endpoint, method = 'GET', data = null, token = null){
  if(!token) throw new Error('Missing access token');
  
  const BASE_URL ='https://api.zoom.us/v2';
  const options ={
    method: method,
    headers:{
      'Authorization': 'Bearer ' + token,
      'Content-Type': 'application/json',
    },
    muteHttpExceptions: true,
  };

  if(data){
    options.payload = JSON.stringify(data);
  }

  //Perform request
  const response = UrlFetchApp.fetch(BASE_URL + endpoint, options);
  const code = response.getResponseCode();
  const text = response.getContentText();

  //Handle response
  if(code >= 200 && code < 300){
    try{
      return JSON.parse(text);
    } catch(err){
      return text; 
    }
  }else{
    const shortText = text.length > 300 ? text.substring(0, 300) + '...' : text;
    throw new Error(`Zoom API error ${code}: ${shortText}`);
  }
}

//Create
function createMeeting(sheet, meetingTypeCell){
  const token = sheet.getRange(cells.Token).getValue();
  if (!token) throw new Error("Missing Token in B1");

  let type = 2; // Default to Schedule
  if(meetingTypeCell === cells.Instant) type = 1;
  if(meetingTypeCell === cells.Recurring) type = 8;

  const topicMap = {
    1: "Test Instant",
    2: "Test Scheduled",
    8: "Test Recurring",
  };

  const data ={
    topic: topicMap[type],
    type: type,
    duration: 40,
    timezone: 'Asia/Kuala_Lumpur',
  };
  if(type !== 1){
    const data ={
      start_time: formatISO(sheet.getRange(cells.Date).getValue()),
    };
  }
  if(type === 8){
    data.recurrence ={
      type: 1,
      repeat_interval: 1,
      endTimes: 3,
    }
  }

  const result = zoomApi("/users/me/meetings", "POST", data, token);
  sheet.getRange(cells.Current).setValue(result.id);
}


//Get
function getMeeting(sheet, meetingId){
  
  const token = sheet.getRange(cells.Token).getValue();
  if(!token) throw new Error("Missing Token");

  meetingId = meetingId || sheet.getRange(cells.Current).getValue();
  if (!meetingId) throw new Error("Missing Meeting ID");

  try{
    const result = zoomApi(`/meetings/${meetingId}`, 'GET', null, token);

    clearCells(sheet, `${cells.Daily}:${cells.MonthDay}`, cells.EndDate);
    clearCells(sheet, `${cells.Delete}:${cells.selectedDays}`, cells.Date);

    sheet.getRange(cells.Topic).setValue(result.topic);
    sheet.getRange(cells.Date).setValue(new Date(result.start_time));
    sheet.getRange(cells.Duration).setValue(result.duration);
    sheet.getRange(cells.Password).setValue(result.password);
  }catch(err){
    sheet.getRange("C2").setValue(`Error: ${err.message}`);
  }

}

//Update
function editMeeting(sheet, meeting, newValue){
  const token = sheet.getRange(cells.Token).getValue();
  if(!token || !meetingId){
    sheet.getRange("C2").setValue("Missing Meeting ID");
    return;
  }

  let type = 2; 
  if(sheet.getRange(cells.Instant).getValue() === true) type = 1;
  if(sheet.getRange(cells.Recurring).getValue() === true) type = 8;

  const data ={
    topic: sheet.getRange(cells.Topic).getValue(),
    type: type,
    start_time: formatISO(sheet.getRange(cells.Date).getValue()),
    duration: sheet.getRange(cells.Duration).getValue(),
    password: sheet.getRange(cells.Password).getValue(),
  };

  if(type === 8){ //Recurring
    data.recurrence = getRecurrenceData(sheet);
  }

  zoomApi(`/meetings/${meetingId}`, 'PATCH', data, token);
  sheet.getRange("C2").setValue(`Updated: ${meetingId}`);
}

//Delete
function deleteMeeting(sheet, newValue){
  if(newValue !== true) return;
  
  const token = sheet.getRange(cells.Token).getValue();
  const meetingId = sheet.getRange(cells.Current).getValue();
  if(!token || !meetingId){
    sheet.getRange("C3").setValue("Missing Token or ID");
    sheet.getRange(cells.Delete).setValue(false);
    return;
  }

  try{
    zoomApi(`/meetings/${meetingId}`,'DELETE', null, token);
    clearCells(sheet, `${cells.Daily}:${cells.MonthDay}`, cells.EndDate);
    clearCells(sheet, `${cells.Current}:${cells.Select}`, cells.Date);
  }catch(err){
    sheet.getRange("C2").setValue(`Delete Error: ${err.message}`);
  }finally{
    sheet.getRange(cells.Delete).setValue(false);
  }
}


function getRecurrenceData(sheet){
  const rec = {};

  if(sheet.getRange(cells.Daily).getValue() === true){
    rec.type = 1;
  }else if(sheet.getRange(cells.Weekly).getValue() === true){
    rec.type = 2;
    const dayMap = {
      [cells.Sunday]: "1",
      [cells.Monday]: "2",
      [cells.Tuesday]: "3",
      [cells.Wednesday]: "4",
      [cells.Thursday]: "5",
      [cells.Friday]: "6",
      [cells.Saturday]: "7",
    };
    let selectedDays = [];
    if(sheet.getRange(cells.Sunday).getValue() === true) selectedDays.push("1");
    if(sheet.getRange(cells.Monday).getValue() === true) selectedDays.push("2");
    if(sheet.getRange(cells.Tuesday).getValue() === true) selectedDays.push("3");
    if(sheet.getRange(cells.Wednesday).getValue() === true) selectedDays.push("4");
    if(sheet.getRange(cells.Thursday).getValue() === true) selectedDays.push("5");
    if(sheet.getRange(cells.Friday).getValue() === true) selectedDays.push("6");
    if(sheet.getRange(cells.Saturday).getValue() === true) selectedDays.push("7");
    rec.weekly_days = selectedDays.join(",");
    
  }else if(sheet.getRange(cells.Monthly).getValue() === true){
    rec.type = 3;
    const dayOfMonth = sheet.getRange(cells.MonthDay).getValue();
    if(dayOfMonth) rec.monthly_day = parseInt(dayOfMonth);
  }

  rec.repeat_interval = sheet.getRange(cells.Interval).getValue() || 1;

  // End Type
  const endTimes = sheet.getRange(cells.EndTimes).getValue();
  const endDate = sheet.getRange(cells.EndDate).getValue();

  if(endTimes){
    rec.end_times = parseInt(endTimes);
    sheet.getRange(endTimes).setBackground("#b7e1cd");
    sheet.getRange(endDate).setBackground(null);
  }else if(endDate){
    rec.end_date_time = formatISO(endDate);
    sheet.getRange(endDate).setBackground("#b7e1cd");
    sheet.getRange(endTimes).setBackground(null);
  }
  
  return rec;
}

function formatISO(date){
  if(!date || !(date instanceof Date)){
    date = new Date();
    date.setHours(date.getHours() + 1);
  }
  
  return Utilities.formatDate(date, "GMT", "yyyy-MM-dd'T'HH:mm:ss'Z'");
}

function recureType(sheet, meeting, newValue){
  if(newValue === true){
    if(meeting === cells.Daily){
      sheet.getRange(cells.Weekly).setValue(false);
      sheet.getRange(cells.Monthly).setValue(false);

      clearCells(sheet, `${cells.Monday}:${cells.MonthDay}`, cells.EndDate);

    }else if(meeting === cells.Weekly){
      sheet.getRange(cells.Daily).setValue(false);
      sheet.getRange(cells.Monthly).setValue(false);

      sheet.getRange(cells.MonthDay).setValue("");

    }else if(meeting === cells.Monthly){
      sheet.getRange(cells.Daily).setValue(false);
      sheet.getRange(cells.Weekly).setValue(false);

      clearCells(sheet, `${cells.Monday}:${cells.Sunday}`, cells.EndDate);

    }
  }
}

function clearCells(sheet, cellArray, ignore){
  const range = sheet.getRange(cellArray);
  const values = range.getValues();
  const validation = range.getDataValidations();

  for(let i = 0; i < values.length; i++){
    const row = range.getRow() + i;
    if(ignore && cells.Date === ignore || ignore && cells.EndDate === ignore) continue;

    const rule = (validation[i] && validation[i][0]) ? validation[i][0] : null;
    if(rule && rule.getCriteriaType && rule.getCriteriaType() === SpreadsheetApp.DataValidationCriteria.CHECKBOX){
      values[i][0] = false;
    }else{
      values[i][0] = "";
    }
  }

  range.setValues(values);
  //range.clearFormat();  //if want to clear formatting
}
