// ... (code from onOpen to setupTrigger is unchanged) ...

/**
 * --- STEP 3: RENAMED THIS FUNCTION ---
 * Was "onEdit", now "onEditHandler". This is the main
 * trigger function that will be installed.
 */
function onEditHandler(e) {
  //Loop Prevention
  const lock = LockService.getScriptLock();
  if (!lock.tryLock(10000)) {
    return;
  }

  try {
    const range = e.range;
    const sheet = range.getSheet();
    const meeting = range.getA1Notation();
    const newValue = e.value;

    if (sheet.getName() !== SheetName) {
      return;
    }

    //Logic
    if (meeting === cells.Token) {
      tokenEdit(sheet, newValue);
    } else if (meeting === cells.Current) {
      getMeeting(sheet, newValue);
    } else if (meeting === cells.Delete) {
      deleteMeeting(sheet, newValue);
    } else if (meeting === cells.Instant || meeting === cells.Schedule || meeting === cells.Recurring) {
      
      // This function just unchecks the other boxes
      meetingType(sheet, meeting, newValue); 

      // --- THIS IS THE UPDATED LOGIC ---
      if (newValue === true) { // Only act when *checking* a box
        const currentMeetingId = sheet.getRange(cells.Current).getValue();
        if (!currentMeetingId) {
          // No ID exists, so CREATE a new pre-generated meeting
          createMeeting(sheet, meeting);
        } else {
          // An ID *does* exist, so UPDATE the meeting type
          editMeeting(sheet, meeting, newValue);
        }
      }

    } else if (meeting === cells.Daily || meeting === cells.Weekly || meeting === cells.Monthly) {
      // This function unchecks other recurrence boxes
      recureType(sheet, meeting, newValue);
      
      // This function updates the existing meeting with the new recurrence
      // This is what you wanted! It works.
      editMeeting(sheet, meeting, newValue);

    } else if (
      meeting === cells.Topic || meeting === cells.Date || meeting === cells.Duration ||
      meeting === cells.Password || meeting === cells.Personal || meeting === cells.Select ||
      meeting === cells.Interval || meeting === cells.Occurance || meeting === cells.EndDate ||
      meeting === cells.EndTimes || meeting === cells.Monday || meeting === cells.Tuesday ||
      meeting === cells.Wednesday || meeting === cells.Thursday || meeting === cells.Friday ||
      meeting === cells.Saturday || meeting === cells.Sunday || meeting === cells.MonthDay
    ) {
      // Any other edit to a detail cell also triggers an update
      editMeeting(sheet, meeting, newValue);
    }

  } catch (err) {
    Logger.log(`onEdit Error: ${err.message} \nStack: ${err.stack}`);
    SpreadsheetApp.getActive().toast(`Error: ${err.message}`, "Script Error", 5);
  } finally {
    //Stop Loop Prevention
    lock.releaseLock();
  }
}


// ... (tokenEdit and meetingType are unchanged) ...


//---------------------Zoom-------------------------
// ... (zoomApi helper function is unchanged) ...

//Create
/**
 * --- THIS FUNCTION IS NOW A "PRE-GENERATOR" ---
 * It checks for empty values and sets defaults before creating.
 */
function createMeeting(sheet, meetingTypeCell) {
  const token = sheet.getRange(cells.Token).getValue();
  if (!token) throw new Error("Missing Token in B1");

  let type = 2; // Default to Schedule
  if (meetingTypeCell === cells.Instant) type = 1;
  if (meetingTypeCell === cells.Recurring) type = 8;

  // --- NEW "PRE-GENERATION" LOGIC ---
  // Check for existing values first, use default if empty.
  let topic = sheet.getRange(cells.Topic).getValue();
  if (!topic) {
    const topicMap = {
      1: "Instant Meeting",
      2: "Scheduled Meeting",
      8: "Recurring Meeting",
    };
    topic = topicMap[type];
    sheet.getRange(cells.Topic).setValue(topic); // Write default back to sheet
  }

  let duration = sheet.getRange(cells.Duration).getValue();
  if (!duration) {
    duration = 40;
    sheet.getRange(cells.Duration).setValue(duration); // Write default back to sheet
  }


  const data = {
    topic: topic,
    type: type,
    duration: duration,
    timezone: 'Asia/Kuala_Lumpur', // You could also read this from a cell
  };

  if (type !== 1) {
    // Get date from sheet, or set a default if blank
    let date = sheet.getRange(cells.Date).getValue();
    if (!date || !(date instanceof Date)) {
      date = new Date();
      date.setHours(date.getHours() + 1);
      sheet.getRange(cells.Date).setValue(date); // Write default back
    }
    data.start_time = formatISO(date);
  }

  if (type === 8) {
    // --- IMPORTANT ---
    // Read recurrence data from the sheet *at creation time*.
    // This lets a user check "Weekly" and "Monday" *before* checking "Recurring".
    data.recurrence = getRecurrenceData(sheet);
  }

  const result = zoomApi("/users/me/meetings", "POST", data, token);
  
  // Set the new ID
  sheet.getRange(cells.Current).setValue(result.id);
  
  // After creating, call getMeeting() to populate the sheet
  // with all the final data from Zoom (like password, join_url, etc.)
  getMeeting(sheet, result.id);
  sheet.getRange("C2").setValue(`Created: ${result.id}`);
}


//Get
function getMeeting(sheet, meetingId) {

  const token = sheet.getRange(cells.Token).getValue();
  if (!token) throw new Error("Missing Token");

  // This block now handles clearing the sheet if B2 is empty
  if (!meetingId) {
    clearCells(sheet, "Details");
    clearCells(sheet, "Recurrance");
    clearCells(sheet, "MeetingType");
    sheet.getRange("C2").setValue("");
    return;
  }

  try {
    const result = zoomApi(`/meetings/${meetingId}`, 'GET', null, token);

    // Clear old data first to prevent mixed-up settings
    clearCells(sheet, "Details");
    clearCells(sheet, "Recurrance");
    clearCells(sheet, "MeetingType");

    // Populate data
    sheet.getRange(cells.Topic).setValue(result.topic);
    sheet.getRange(cells.Date).setValue(new Date(result.start_time));
    sheet.getRange(cells.Duration).setValue(result.duration);
    sheet.getRange(cells.Password).setValue(result.password);
    
    // Set meeting type checkbox
    if(result.type === 1) sheet.getRange(cells.Instant).setValue(true);
    else if (result.type === 8) sheet.getRange(cells.Recurring).setValue(true);
    else sheet.getRange(cells.Schedule).setValue(true);

    // Populate recurrence
    if (result.recurrence) {
      const rec = result.recurrence;
      if (rec.type === 1) sheet.getRange(cells.Daily).setValue(true);
      if (rec.type === 2) {
        sheet.getRange(cells.Weekly).setValue(true);
        const days = rec.weekly_days.split(',');
        if (days.includes("1")) sheet.getRange(cells.Sunday).setValue(true);
        if (days.includes("2")) sheet.getRange(cells.Monday).setValue(true);
        if (days.includes("3")) sheet.getRange(cells.Tuesday).setValue(true);
        if (days.includes("4")) sheet.getRange(cells.Wednesday).setValue(true);
        if (days.includes("5")) sheet.getRange(cells.Thursday).setValue(true);
        if (days.includes("6")) sheet.getRange(cells.Friday).setValue(true);
        if (days.includes("7")) sheet.getRange(cells.Saturday).setValue(true);
      }
      if (rec.type === 3) {
        sheet.getRange(cells.Monthly).setValue(true);
        if(rec.monthly_day) sheet.getRange(cells.MonthDay).setValue(rec.monthly_day);
      }
      sheet.getRange(cells.Interval).setValue(rec.repeat_interval);
      if(rec.end_times) sheet.getRange(cells.EndTimes).setValue(rec.end_times);
      if(rec.end_date_time) sheet.getRange(cells.EndDate).setValue(new Date(rec.end_date_time));
    }

    sheet.getRange("C2").setValue(`Loaded: ${result.id}`);

  } catch (err) {
    sheet.getRange("C2").setValue(`Error: ${err.message}`);
  }

}

//Update
function editMeeting(sheet, meeting, newValue) {
  const token = sheet.getRange(cells.Token).getValue();
  const meetingId = sheet.getRange(cells.Current).getValue();

  if (!token || !meetingId) {
    // This is fine. If the user clicks "Daily" before a meeting is created,
    // we just stop. The create will happen when they click "Recurring".
    Logger.log("editMeeting called, but no meeting ID. Stopping.");
    return;
  }

  let type = 2; // Default Schedule
  if (sheet.getRange(cells.Instant).getValue() === true) type = 1;
  if (sheet.getRange(cells.Recurring).getValue() === true) type = 8;

  const data = {
    topic: sheet.getRange(cells.Topic).getValue(),
    type: type,
    start_time: formatISO(sheet.getRange(cells.Date).getValue()),
    duration: sheet.getRange(cells.Duration).getValue(),
    password: sheet.getRange(cells.Password).getValue(),
  };

  if (type === 8) { //Recurring
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


function getRecurrenceData(sheet) {
  const rec = {};

  if (sheet.getRange(cells.Daily).getValue() === true) {
    rec.type = 1;
  } else if (sheet.getRange(cells.Weekly).getValue() === true) {
    rec.type = 2;

    // Simpler way to get weekly days
    const weekDayCells = [
      cells.Sunday, cells.Monday, cells.Tuesday, cells.Wednesday,
      cells.Thursday, cells.Friday, cells.Saturday
    ];
    const dayMap = ["1", "2", "3", "4", "5", "6", "7"];

    let selectedDays = [];
    sheet.getRangeList(weekDayCells).getRanges().forEach((range, index) => {
      if (range.getValue() === true) {
        selectedDays.push(dayMap[index]);
      }
    });
    rec.weekly_days = selectedDays.join(",");

  } else if (sheet.getRange(cells.Monthly).getValue() === true) {
    rec.type = 3;
    const dayOfMonth = sheet.getRange(cells.MonthDay).getValue();
    if (dayOfMonth) {
      rec.monthly_day = parseInt(dayOfMonth);
    } else {
      rec.monthly_day = 1; // Default to 1 if empty
    }
  }

  // Ensure interval is at least 1
  rec.repeat_interval = sheet.getRange(cells.Interval).getValue() || 1;

  // End Type
  const endTimes = sheet.getRange(cells.EndTimes).getValue();
  const endDate = sheet.getRange(cells.EndDate).getValue();

  if (endTimes) {
    rec.end_times = parseInt(endTimes);
  } else if (endDate) {
    rec.end_date_time = formatISO(endDate);
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

function recureType(sheet, meeting, newValue) {
  if (newValue === true) { // Only pre-generate when *checking* the box

    // Set default interval if it's empty
    if (!sheet.getRange(cells.Interval).getValue()) {
      sheet.getRange(cells.Interval).setValue(1);
    }

    if (meeting === cells.Daily) {
      sheet.getRange(cells.Weekly).setValue(false);
      sheet.getRange(cells.Monthly).setValue(false);

      clearCells(sheet, "Recurrance_WeeklyOnly");
      clearCells(sheet, "Recurrance_MonthlyOnly");

    } else if (meeting === cells.Weekly) {
      sheet.getRange(cells.Daily).setValue(false);
      sheet.getRange(cells.Monthly).setValue(false);

      clearCells(sheet, "Recurrance_MonthlyOnly");

      // Pre-gen: Check if any day is selected. If not, default to Monday.
      const weekDays = sheet.getRange("E11:E17").getValues().flat(); // Get all day values
      if (!weekDays.some(day => day === true)) { // .some() checks if any item is true
        sheet.getRange(cells.Monday).setValue(true);
      }

    } else if (meeting === cells.Monthly) {
      sheet.getRange(cells.Daily).setValue(false);
      sheet.getRange(cells.Weekly).setValue(false);

      clearCells(sheet, "Recurrance_WeeklyOnly");

      // Pre-gen: Set default day of month
      if (!sheet.getRange(cells.MonthDay).getValue()) {
        sheet.getRange(cells.MonthDay).setValue(1);
      }
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
