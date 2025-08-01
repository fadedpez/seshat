# T001: Character Creation UI Integration Test

**Date:** July 31, 2025  
**UE Version:** 5.6.0  
**Purpose:** Test complete character creation flow from UI to RPGCharacterSubsystem  
**Prerequisites:** Character integration complete (P007), toolkit DLL compiled and loaded

## Test Objective

Create a comprehensive character creation flow that tests the full D&D 5e character building experience:
- **Race Selection:** Choose from hardcoded race options with ability score previews
- **Stat Rolling:** Use our dice subsystem to roll 4d6 drop lowest for each ability score
- **Class Selection:** Choose from hardcoded class options with feature previews  
- **Proficiency Selection:** Select skill proficiencies based on class/background choices
- **Background Selection:** Choose background with associated skills and features
- **Character Summary:** Display all decisions with calculated final stats
- **Confirm & Save:** Save complete character to local disk storage
- **Integration Testing:** Verify toolkit integration, memory cleanup, and data flow

## D&D 5e Character Creation Flow vs Toolkit Integration

### Page 1: Race Selection
**D&D 5e Requirements:**
- Choose from 9+ core races (Human, Elf, Dwarf, Halfling, Dragonborn, Gnome, Half-Elf, Half-Orc, Tiefling)
- Race provides: Ability score increases, size, speed, languages, racial traits, proficiencies

**Toolkit Integration Status:**
- ✅ **Available:** `RPGCharacterSubsystem::CreateCharacter()` accepts race parameter
- ✅ **Available:** Races tested: "human", "elf", "dwarf", "halfling" 
- ❌ **Missing:** No way to get list of available races dynamically
- ❌ **Missing:** No way to preview race bonuses/features before selection

**Implementation:** Hardcode race buttons and descriptions for now

### Page 2: Ability Score Determination
**D&D 5e Requirements:**
- Standard Array (15, 14, 13, 12, 10, 8) OR
- Point Buy (27 points to distribute) OR  
- Rolling (4d6 drop lowest, 6 times)
- Assign scores to STR, DEX, CON, INT, WIS, CHA

**Toolkit Integration Status:**
- ✅ **Available:** `RPGDiceSubsystem::Roll()` can roll 4d6 for stat rolling
- ❌ **Missing:** No "drop lowest" dice mechanic in current integration
- ❌ **Missing:** No point-buy system
- ❌ **Missing:** No standard array option

**Implementation:** Use `RPGDiceSubsystem::Roll(6)` six times (simulate 4d6 drop lowest with single d6)

### Page 3: Class Selection  
**D&D 5e Requirements:**
- Choose from 12+ core classes (Fighter, Wizard, Rogue, Cleric, Barbarian, Bard, Druid, Monk, Paladin, Ranger, Sorcerer, Warlock)
- Class provides: Hit die, proficiencies, saving throws, starting equipment, class features

**Toolkit Integration Status:**
- ✅ **Available:** `CreateCharacter()` accepts class parameter
- ✅ **Available:** Classes tested: "fighter", "wizard", "rogue", "cleric"
- ❌ **Missing:** No way to get available classes dynamically
- ❌ **Missing:** No way to preview class features/proficiencies

**Implementation:** Hardcode class buttons and descriptions

### Page 4: Background Selection
**D&D 5e Requirements:**
- Choose background (Acolyte, Criminal, Folk Hero, Noble, Sage, Soldier, etc.)
- Background provides: Skill proficiencies, languages, equipment, special feature

**Toolkit Integration Status:**
- ✅ **Available:** `CreateCharacter()` accepts background parameter  
- ✅ **Available:** Backgrounds tested: "soldier", "criminal", "acolyte", "folk-hero"
- ❌ **Missing:** No way to get available backgrounds dynamically
- ❌ **Missing:** No way to preview background benefits

**Implementation:** Hardcode background buttons and descriptions

### Page 5: Skill Proficiencies (Class-Based)
**D&D 5e Requirements:**
- Each class offers choice of proficiencies (e.g., Fighter: choose 2 from Acrobatics, Animal Handling, Athletics, History, Insight, Intimidation, Perception, Survival)
- Background may provide additional fixed proficiencies

**Toolkit Integration Status:**
- ❌ **Missing:** No skill proficiency selection system in current integration
- ❌ **Missing:** No way to get class-specific skill options
- ❌ **Missing:** Current `CreateCharacter()` doesn't take skill choices

**Implementation:** Skip for now - note as toolkit limitation

### Page 6: Subclass/Archetype Selection (Level 1+ depending on class)
**D&D 5e Requirements:**
- Some classes choose subclass at level 1 (Cleric Domain, Warlock Patron)
- Others at level 2-3 (Fighter Archetype, Wizard School)

**Toolkit Integration Status:**
- ❌ **Missing:** No subclass system in current integration
- ❌ **Missing:** Current characters are basic level 1 without subclass choices

**Implementation:** Skip for now - note as future enhancement

### Page 7: Equipment Selection
**D&D 5e Requirements:**
- Starting equipment from class + background OR
- Buy equipment with starting gold
- Affects AC, attack bonuses, available actions

**Toolkit Integration Status:**
- ❌ **Missing:** No equipment system in current integration
- ❌ **Missing:** AC calculation doesn't account for armor
- ❌ **Missing:** No starting equipment assignment

**Implementation:** Skip for now - note as major toolkit gap

### Page 8: Final Character Summary & Save
**D&D 5e Requirements:**
- Show complete character with all calculated stats
- Final ability scores (base + racial)
- Hit points, AC, proficiency bonus, initiative
- All features, proficiencies, equipment

**Toolkit Integration Status:**
- ✅ **Available:** `FCharacterResult` provides most calculated stats
- ✅ **Available:** Ability scores, HP, AC, initiative, speed included
- ✅ **Available:** Features array populated
- ❌ **Partial:** AC/HP calculations may not account for equipment
- ❌ **Missing:** No save-to-disk functionality yet

**Implementation:** Display `FCharacterResult` data, save as JSON file

## Achievable Test Flow (Hardcoded + Toolkit Integration)

**Page 1:** Race Selection
- Hardcoded races: Human (+1 all stats), Elf (+2 DEX), Dwarf (+2 CON), Halfling (+2 DEX)
- Hardcoded descriptions of racial features

**Page 2:** Ability Score Rolling (4d6 Drop Lowest Simulation)
- Use `RPGDiceSubsystem::Roll(6)` four times per ability score
- Blueprint logic: drop 2 lowest rolls, sum remaining 2
- Roll all 6 abilities: STR, DEX, CON, INT, WIS, CHA

**Page 3:** Class Selection  
- Hardcoded classes: Fighter (d10 HD), Wizard (d6 HD), Rogue (d8 HD), Cleric (d8 HD)
- Hardcoded descriptions of class features and proficiencies

**Page 4:** Skill Proficiency Selection (Simulated)
- Hardcoded skill list: Athletics, Stealth, Perception, Investigation, Persuasion, Intimidation, History, Medicine
- UI flow: "Choose 2 skills" with checkboxes
- Simulate class restrictions (Fighter gets Athletics/Intimidation options, Rogue gets Stealth/Investigation, etc.)

**Page 5:** Basic Equipment Selection (Simulated)
- Hardcoded equipment: Leather Armor (+1 AC), Chain Mail (+3 AC), Shield (+2 AC), Sword, Bow, Staff
- Simple selection: "Choose armor" and "Choose weapon"
- Show AC impact in preview

**Page 6:** Background Selection
- Hardcoded backgrounds: Soldier (Athletics proficiency), Criminal (Stealth proficiency), etc.
- May add proficiencies already selected in step 4

**Page 7:** Character Summary & Save
- Apply racial bonuses to rolled stats
- Calculate final AC (base + armor + DEX modifier)
- Display all selections and final stats
- Use `CreateCharacter()` for final character generation
- Save complete character data to JSON file

**Testing Goals:**
- ✅ Multi-page UI navigation and state management
- ✅ Dice subsystem integration with custom logic
- ✅ Complex selection flows (skills, equipment)
- ✅ Data calculation and preview systems
- ✅ Character creation pipeline integration
- ✅ Local file persistence

## Implementation Steps

### Step 1: Create UI Folder Structure
1. **Open Content Browser** (usually docked at bottom of UE Editor)
2. **Navigate to Content folder** (root folder in Content Browser)
3. **Create UI folder:**
   - Right-click in Content Browser → "New Folder"
   - Name it "UI"
4. **Enter UI folder** (double-click to open)
5. **Create CharacterCreation subfolder:**
   - Right-click in UI folder → "New Folder" 
   - Name it "CharacterCreation"

### Step 2: Create Main Character Creation Widget
1. **Navigate to Content/UI/CharacterCreation/** in Content Browser
2. **Create main widget:**
   - Right-click in CharacterCreation folder
   - Select "User Interface" → "Widget Blueprint"
   - Name it "WBP_CharacterCreationMain"
3. **Create page widgets:** (Repeat for each)
   - Right-click → "User Interface" → "Widget Blueprint"
   - Create these widgets:
     - `WBP_RaceSelection`
     - `WBP_ClassSelection` 
     - `WBP_BackgroundSelection`
     - `WBP_CharacterSummary`

### Step 3: Setup Main Widget Structure
**Open WBP_CharacterCreationMain (double-click in Content Browser):**

**What you'll see:** UE opens the Widget Blueprint editor. You'll see:
- Large gray area in center (the "Designer" view - this is your UI canvas)
- "Palette" panel on left (list of UI components you can add)
- "Hierarchy" panel on left (shows what you've added, like a folder tree)
- "Details" panel on right (settings for whatever you select)

1. **Add Root Canvas Panel (Foundation Layer):**
   
   **Why:** Every UI needs a foundation. Canvas Panel is like the base layer everything else sits on.
   
   - Look at "Palette" panel on left side
   - Type "Canvas Panel" in search box at top of Palette
   - You should see "Canvas Panel" appear in the list
   - Click and drag "Canvas Panel" onto the gray canvas area in center
   - **Result:** You should see "Canvas Panel" appear in the Hierarchy panel (left side)
   - **Visual:** The gray canvas area might show a faint outline

2. **Add Widget Switcher (Page Container):**
   
   **Why:** Widget Switcher is like a book - it can show one page at a time and flip between them.
   
   - In Palette search box, clear "Canvas Panel" and type "Widget Switcher"
   - Drag "Widget Switcher" from Palette onto the Canvas Panel (aim for the center of gray area)
   - **Important:** Drop it ON the gray area, not on the Hierarchy panel
   - **Result:** Hierarchy should now show:
     ```
     Canvas Panel
     └── Widget Switcher
     ```

3. **Make Widget Switcher Fill Screen:**
   
   **Why:** We want our character creation to use the whole screen.
   
   - Click on "Widget Switcher" in the Hierarchy panel (left side)
   - Look at Details panel (right side) - you should see lots of settings
   - Look for a section that mentions anchors or positioning
   - **If you see anchor controls:** Set them to fill/stretch
   - **If you don't see anchor controls:** That's fine, we'll fix sizing later
   - **Goal:** Widget Switcher should cover the whole gray canvas area

4. **Add Pages to Widget Switcher:**
   
   **What we need:** Widget Switcher needs "pages" to switch between. Each page needs its own container.
   
   **The Working Method (Canvas Panel Children):**
   - From Palette, search for "Canvas Panel"
   - Drag "Canvas Panel" from Palette directly onto "Widget Switcher" in Hierarchy panel  
   - Repeat 6 more times (7 total pages for our character creation flow)
   - Each Canvas Panel becomes a "page" that Widget Switcher can show/hide
   
   **Result:** Hierarchy should show:
   ```
   Canvas Panel (Root)
   └── Widget Switcher
       ├── Canvas Panel (Page 1 - Race Selection)
       ├── Canvas Panel (Page 2 - Ability Rolling)  
       ├── Canvas Panel (Page 3 - Class Selection)
       ├── Canvas Panel (Page 4 - Skill Selection)
       ├── Canvas Panel (Page 5 - Equipment Selection)
       ├── Canvas Panel (Page 6 - Background Selection)
       └── Canvas Panel (Page 7 - Character Summary)
   ```
   
   **Why this works:** Each Canvas Panel acts as a container for that page's UI elements. Widget Switcher shows one Canvas Panel at a time.

3. **Add Page Content:**
   - In Hierarchy panel, click on "Widget Switcher Slot 0"
   - From Palette panel, search for "Text Block" (not just "Text")
   - Drag "Text Block" into the slot area on canvas
   - With text selected, in Details panel find "Content" → "Text" field
   - Set text to "Race Selection Page"
   - Repeat for other slots:
     - Slot 1: "Class Selection Page"
     - Slot 2: "Background Selection Page" 
     - Slot 3: "Character Summary Page"

4. **Add Navigation Buttons:**
   - From Palette, search for "Button" and drag onto canvas (below Widget Switcher)
   - With button selected, from Palette drag "Text Block" onto the button
   - Select the text block, in Details → Content → Text, set to "Next Page"
   - Select the button, press Ctrl+D to duplicate
   - Change duplicated button's text to "Previous Page"

### Step 4: Add Blueprint Variables
**Switch to Graph view (click "Graph" tab at top):**

1. **Add Variables:**
   - In "My Blueprint" panel (usually left side), look for "Variables" section
   - Click the "+" button next to "Variables"
   - This creates "NewVar_0" - click it to select
   - In Details panel (right side), find "Variable Name" field and rename
   - Create these variables:
     - `SelectedRace`
     - `SelectedClass` 
     - `SelectedBackground`
     - `CharacterName`
     - `CurrentPageIndex`
     - `CreatedCharacter`

2. **Set Variable Types:**
   - Click each variable in My Blueprint panel to select it
   - In Details panel, find "Variable Type" dropdown (blue pill-shaped button)
   - Click dropdown and set types:
     - SelectedRace, SelectedClass, SelectedBackground, CharacterName: String
     - CurrentPageIndex: Integer  
     - CreatedCharacter: Search for "FCharacterResult" (may need to uncheck "Context Sensitive")

### Step 5: Add Navigation Logic
**In Graph view of WBP_CharacterCreationMain:**

1. **Add Next Page Function:**
   - In "My Blueprint" panel, click "+" next to Functions
   - Name it "NextPage"
   - In the function graph:
     - Add "Get Current Page Index" → "Integer + Integer" (add 1)
     - Connect to "Set Active Widget Index" (from Widget Switcher reference)
     - Update "Current Page Index" variable

2. **Wire Up Next Button:**
   - Go back to Designer view (click "Designer" tab)
   - Select your "Next Page" button
   - In Details panel, scroll to "Events" section
   - Click "+" next to "On Clicked"
   - This opens Graph view with button event
   - Right-click → search "NextPage" → select your NextPage function
   - Connect the execution pins

3. **Add Previous Page Logic:** (Similar to Next Page but subtract 1)

### Step 6: Add Character Creation Logic  
**In WBP_CharacterCreationMain Graph view:**

1. **Create Character Function:**
   - In "My Blueprint" panel, click "+" next to Functions
   - Name it "CreateCharacter"
   - In the function graph:
     - Right-click → search "Get Game Instance Subsystem"
     - Set Class to "RPG Character Subsystem"
     - From the subsystem output, drag and search "Create Character"
     - Connect Name, SelectedRace, SelectedClass, SelectedBackground variables
     - Store the return value in "CreatedCharacter" variable

2. **Add Create Button Logic:**
   - Go to Designer view, add a "Create Character" button on page 3
   - Select button → Details panel → Events → "+" next to "On Clicked"  
   - In the event graph, call your "CreateCharacter" function
   - Add error checking: drag from CreatedCharacter → "Break FCharacterResult" → check "Has Error"

### Step 7: Create Simple Race Selection Page
**Open WBP_RaceSelection widget:**

1. **Add Race Buttons:**
   - Designer view: Add 4 "Button" widgets arranged in a grid
   - Add "Text" widget inside each button
   - Set button texts: "Human", "Elf", "Dwarf", "Halfling"

2. **Add Race Button Logic:**
   - Select "Human" button → Details → Events → "+" next to "On Clicked"
   - In Graph view, drag from execution pin → search "Get Parent"
   - Cast to "WBP Character Creation Main"
   - From cast output → "Set Selected Race" (set to "human")
   - Repeat for other race buttons with appropriate race strings

3. **Add Preview Text:**
   - Designer view: Add large "Text" widget for race preview
   - Name it "RacePreviewText" in the Details panel
   - In Graph view, when race button clicked, also "Set Text" on preview

### Step 8: Create Simple Class Selection Page  
**Open WBP_ClassSelection widget:**

1. **Add Class Buttons:**
   - Add 4 buttons: "Fighter", "Wizard", "Rogue", "Cleric"
   - Follow same pattern as race buttons
   - Set parent widget's "SelectedClass" variable

2. **Add Class Preview:**
   - Add preview text widget
   - Update preview when class selected

### Step 9: Create Simple Background Selection Page
**Open WBP_BackgroundSelection widget:**

1. **Add Background Buttons:** 
   - Add 4 buttons: "Soldier", "Criminal", "Acolyte", "Folk Hero"
   - Set parent widget's "SelectedBackground" variable
   - String values: "soldier", "criminal", "acolyte", "folk-hero"

### Step 10: Create Character Summary Page
**Open WBP_CharacterSummary widget:**

1. **Add Name Input:**
   - Designer view: Add "Text Box" widget (for name input)
   - Add "Text" label above it saying "Character Name:"

2. **Add Character Display:**
   - Add multiple "Text" widgets for displaying character stats
   - Name them: "StatsText", "FeaturesText", "AbilitiesText"
   - Set them to large size for displaying character data

3. **Add Create Button Logic:**
   - Add "Create Character" button
   - Button click event should:
     - Get name from Text Box → Set CharacterName in parent
     - Call parent's CreateCharacter function
     - Display results in the text widgets

### Step 11: Display Character Results
**In WBP_CharacterSummary Graph view:**

1. **Add Display Logic:**
   - After CreateCharacter call succeeds
   - From CreatedCharacter variable → "Break FCharacterResult"
   - Format text strings showing:
     - Name, Race, Class, Background
     - Ability scores (Strength, Dexterity, etc.)
     - Hit Points, Armor Class, Speed
     - Features array (convert to readable text)

2. **Add Error Display:**
   - If HasError is true, display ErrorMessage instead of stats

## Test Execution Steps

### 1. Launch Test  
1. **Compile All Widgets:**
   - Open each widget Blueprint (WBP_CharacterCreationMain, etc.)
   - Click "Compile" button at top toolbar
   - Fix any compilation errors

2. **Create Test Level:**
   - File menu → New Level → Basic Level
   - Save as "CharacterCreationTest"

3. **Add UI to Level:**
   - In level editor, go to Blueprints menu → Open Level Blueprint
   - In Level Blueprint Graph:
     - Right-click → search "Create Widget"
     - Set Class to "WBP Character Creation Main"  
     - From "Create Widget" output → "Add to Viewport"
     - Connect from "Event BeginPlay"

4. **Test in PIE (Play in Editor):**
   - Click "Play" button in level editor
   - Your character creation UI should appear

### 2. Test Complete Flow
1. **Race Selection:** Click different races, verify preview updates
2. **Class Selection:** Navigate back/forward, verify state preserved
3. **Background Selection:** Complete selection process
4. **Character Creation:** Enter name, click "Create Character"
5. **Verify Results:** Character stats populate correctly

### 3. Error Testing
1. **Missing Selections:** Try advancing without making selections
2. **Invalid Combinations:** Test with empty strings or invalid data
3. **Toolkit Errors:** Verify error messages display properly

### 4. Memory Testing  
1. **Repeat Creation:** Create multiple characters in succession
2. **Monitor Memory:** Use UE's Stat Memory console command
3. **Verify Cleanup:** No memory leaks from CGO automatic cleanup

## Expected Results

### Success Criteria
- **UI Navigation:** All pages navigate correctly with state preservation
- **Character Creation:** `CreateCharacter()` returns valid `FCharacterResult`
- **Data Display:** All character stats and features display correctly
- **Error Handling:** Invalid inputs show appropriate error messages
- **Memory Management:** No memory leaks or crashes during repeated creation

### Example Success Output
```
Character Created Successfully:
Name: Thorin Ironforge
Race: Dwarf (Mountain Dwarf)
Class: Fighter (Level 1) 
Background: Soldier

Ability Scores:
STR: 15 (+2), DEX: 12 (+1), CON: 15 (+2)
INT: 10 (+0), WIS: 13 (+1), CHA: 8 (-1)

Combat Stats:
Hit Points: 12, Armor Class: 16, Initiative: +1, Speed: 25ft

Features:
- Darkvision (60 feet)
- Dwarven Resilience  
- Combat Training
- Military Rank
- Vehicle Proficiency
```

## Troubleshooting

### Common Issues
1. **Compilation Errors:** Verify `RPGCharacterSubsystem` is accessible in Blueprint
2. **Missing Data:** Check that toolkit DLL is loaded and functions are bound
3. **UI Navigation:** Ensure Widget Switcher indices match page order
4. **Memory Issues:** Verify automatic cleanup is working with repeated tests

### Debug Steps
1. **Blueprint Debugging:** Use print statements to verify variable values
2. **Subsystem Testing:** Test `CreateCharacter()` directly in Blueprint
3. **DLL Verification:** Check that toolkit functions are loading properly
4. **Error Analysis:** Use Blueprint debugger to trace execution flow

## Test Success Indicators

1. **✅ Complete Flow:** User can navigate through all 4 pages
2. **✅ Character Creation:** `CreateCharacter()` succeeds with valid inputs  
3. **✅ Data Display:** All FCharacterResult fields populate in UI
4. **✅ Error Handling:** Invalid inputs handled gracefully
5. **✅ Memory Stability:** No crashes or leaks during repeated use
6. **✅ State Management:** Selections preserved during navigation

## Next Steps After Success

1. **Storage Integration:** Add repository layer to persist created characters
2. **Enhanced UI:** Improve visual design and user experience
3. **Dynamic Data:** Replace hardcoded lists with toolkit-provided options
4. **Validation:** Add more sophisticated input validation
5. **Character Management:** Build character roster and editing features

This test validates the complete character integration pipeline and establishes the foundation for more advanced character management features.