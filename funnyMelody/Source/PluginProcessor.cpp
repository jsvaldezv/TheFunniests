#include "PluginProcessor.h"
#include "PluginEditor.h"

FunnyMelodyAudioProcessor::FunnyMelodyAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    example1(true);
}

FunnyMelodyAudioProcessor::~FunnyMelodyAudioProcessor(){}

void FunnyMelodyAudioProcessor::printModel(const Clasp::OutputTable& out, const Clasp::Model& model)
{
    std::cout << "Model " << model.num << ": \n";
    
    // Always print facts.
    for (Clasp::OutputTable::fact_iterator it = out.fact_begin(), end = out.fact_end(); it != end; ++it)
        std::cout << *it << " ";
    
    // Print elements that are true wrt the current model.
    for (Clasp::OutputTable::pred_iterator it = out.pred_begin(), end = out.pred_end(); it != end; ++it)
    {
        if (model.isTrue(it->cond))
            std::cout << it->name << " ";
    }
    
    // Print additional output variables.
    for (Clasp::OutputTable::range_iterator it = out.vars_begin(), end = out.vars_end(); it != end; ++it)
        std::cout << (model.isTrue(Clasp::posLit(*it)) ? int(*it) : -int(*it)) << " ";
    
    std::cout << std::endl;
}

void FunnyMelodyAudioProcessor::example1(bool basicSolve)
{
    Clasp::Asp::LogicProgram lp;
    Potassco::RuleBuilder rb;
    Clasp::SharedContext ctx;

    lp.startProgram(ctx);

    Potassco::Atom_t a = lp.newAtom();
    Potassco::Atom_t b = lp.newAtom();
    Potassco::Atom_t c = lp.newAtom();
    
    lp.addRule(rb.start().addHead(a).addGoal(a));
    //lp.addRule(rb.start().addHead(b).addGoal(Potassco::neg(a)));
    lp.addRule(rb.start().addHead(b).addGoal(b));
    lp.addRule(rb.start().addHead(c).addGoal(c));

    lp.addOutput("a", a);
    lp.addOutput("b", b);
    lp.addOutput("c", c);
    //lp.addOutput("~b", Potassco::neg(b));
    //lp.addOutput("eureka", Potassco::toSpan<Potassco::Lit_t>());
    lp.endProgram();

    Clasp::ModelEnumerator enumerator;
    enumerator.init(ctx);

    ctx.endInit();

    if (basicSolve)
    {
        std::cout << "With Clasp::BasicSolve" << std::endl;
        Clasp::BasicSolve solve(*ctx.master());
        enumerator.start(solve.solver());
        
        while (solve.solve() == Clasp::value_true) {
            if (enumerator.commitModel(solve.solver())) { printModel(ctx.output, enumerator.lastModel()); }
            enumerator.update(solve.solver());
        }
        
        std::cout << "No more models!" << std::endl;
    }
    else
    {
        std::cout << "With Clasp::SequentialSolve" << std::endl;
        Clasp::SequentialSolve solve;
        solve.setEnumerator(enumerator);
        solve.start(ctx);
        
        while (solve.next())
            printModel(ctx.output, solve.model());
        if (!solve.more())
            std::cout << "No more models!" << std::endl;
    }
}

void FunnyMelodyAudioProcessor::createMelody (int noteNumber)
{
    // CHANNELS, TIME, NOTAS Y VELOCITY //
    int midiChannel = 0;
    double startTime = juce::Time::getMillisecondCounterHiRes() * 0.001;
    int C = 60;
    float velocity = 100.0f;
    
    // CREATE MIDI MESSAGES //
    auto message = juce::MidiMessage::noteOn(midiChannel, C, velocity);
    message.setTimeStamp(juce::Time::getMillisecondCounterHiRes() * 0.001 - startTime);
    
    auto message1 = juce::MidiMessage::noteOn(midiChannel, C + 5, velocity);
    message1.setTimeStamp(message.getTimeStamp());
    
    auto messageOff = juce::MidiMessage::noteOff(message.getChannel(), message.getNoteNumber());
    messageOff.setTimeStamp(message.getTimeStamp() + 192);
    
    auto messageOff1 = juce::MidiMessage::noteOff(message1.getChannel(), message1.getNoteNumber());
    messageOff1.setTimeStamp(message1.getTimeStamp() + 96);
    
    // CREAR MIDI FILE Y SECUENCIA //
    juce::MidiFile midiFile;
    juce::MidiMessageSequence mmSeq;
    
    // AÑADIR NOTAS MIDI //
    mmSeq.addEvent(message, 0);
    mmSeq.addEvent(message1, 0);
    mmSeq.addEvent(messageOff, 0);
    mmSeq.addEvent(messageOff1, 0);
    
    midiFile.addTrack(mmSeq);
    midiFile.setTicksPerQuarterNote(96);
    
    // GUARDAR ARCHIVO MIDI //
    juce::String desktop = juce::File::getSpecialLocation(juce::File::userDesktopDirectory).getFullPathName();
    juce::File file(desktop + directorySeparator + name + "_" + (juce::String)numMelody + extension);
    juce::FileOutputStream stream(file);
    
    /*if (midiFile.writeTo(stream, 1))
        std::cout << "WriteTo method->true\n";
    else
        std::cout << "WriteTo method->false\n";*/
    
    stream.flush();
    numMelody++;
}

const juce::String FunnyMelodyAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FunnyMelodyAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FunnyMelodyAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FunnyMelodyAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double FunnyMelodyAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FunnyMelodyAudioProcessor::getNumPrograms()
{
    return 1;
}

int FunnyMelodyAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FunnyMelodyAudioProcessor::setCurrentProgram (int index){}

const juce::String FunnyMelodyAudioProcessor::getProgramName (int index)
{
    return {};
}

void FunnyMelodyAudioProcessor::changeProgramName (int index, const juce::String& newName){}

//==============================================================================
void FunnyMelodyAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock){}

void FunnyMelodyAudioProcessor::releaseResources(){}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FunnyMelodyAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void FunnyMelodyAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        //auto* channelData = buffer.getWritePointer (channel);
    }
}

bool FunnyMelodyAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* FunnyMelodyAudioProcessor::createEditor()
{
    return new FunnyMelodyAudioProcessorEditor (*this);
}

void FunnyMelodyAudioProcessor::getStateInformation (juce::MemoryBlock& destData){}

void FunnyMelodyAudioProcessor::setStateInformation (const void* data, int sizeInBytes){}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FunnyMelodyAudioProcessor();
}
