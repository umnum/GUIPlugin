/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Guiplugin2AudioProcessor::Guiplugin2AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ), thumbnailCache(1), thumbnail(1, formatManager, thumbnailCache), writeIndex(0)
#endif
{
    // initialize the AudioParameter values
    addParameter(volume = new AudioParameterFloat("volume", "Volume", 0.0f, 1.0f, 0.5f));
    addParameter(pitch = new AudioParameterFloat("pitch", "Pitch", 20.0f, 1000.0f, 440.0f));
    addParameter(isOn = new AudioParameterBool("toggle", "Toggle On/Off", true));
    
    // set up the audio thumbnail
    formatManager.registerBasicFormats();
    thumbnail.reset(1, getSampleRate());
}

Guiplugin2AudioProcessor::~Guiplugin2AudioProcessor()
{
}

//==============================================================================
const String Guiplugin2AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Guiplugin2AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Guiplugin2AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Guiplugin2AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Guiplugin2AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Guiplugin2AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Guiplugin2AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Guiplugin2AudioProcessor::setCurrentProgram (int index)
{
}

const String Guiplugin2AudioProcessor::getProgramName (int index)
{
    return {};
}

void Guiplugin2AudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void Guiplugin2AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    currentSampleRate = sampleRate;
    updateAngleDelta();
    thumbnailBufferLength = sampleRate*0.1;
    thumbnailBuffer.setSize(getTotalNumInputChannels(), thumbnailBufferLength);
    // the read index is one audio buffer behind the write index
    readIndex = samplesPerBlock;
}

void Guiplugin2AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Guiplugin2AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Guiplugin2AudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    int numSamples = buffer.getNumSamples();
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, numSamples);

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    float** channelData = buffer.getArrayOfWritePointers();
    float** thumbnailData = thumbnailBuffer.getArrayOfWritePointers();
    
    

    if(*isOn) // toggle switch is enabled
    {
        for (auto sample = 0; sample < numSamples; ++sample, ++writeIndex, ++readIndex)
        {
            // get the current sample value of the sine wave
            auto currentSample = (float) std::sin (currentAngle);
            // update the sine wave angle
            currentAngle += angleDelta;
            // thumnail buffer is a circular buffer
            if (writeIndex > thumbnailBufferLength - 1)
            {
                writeIndex = 0;
            }
            if (readIndex > thumbnailBufferLength - 1)
            {
                readIndex = 0;
            }
            for (int channel = 0; channel < totalNumInputChannels; ++channel)
            {
                // update the current gain value
                currentSample*=*volume;
                // write to the audio buffer
                channelData[channel][sample] = currentSample;
                // write to the thumnail buffer
                thumbnailData[channel][writeIndex] = currentSample;
            }
        }

        // copy the thumnail buffer's contents to the audio thumnail, starting from the read index
        thumbnail.reset(1, getSampleRate());
        thumbnail.addBlock(0, thumbnailBuffer, readIndex, thumbnailBufferLength-readIndex);
        thumbnail.addBlock(thumbnailBufferLength - readIndex, thumbnailBuffer, 0, readIndex);
        
    }
}

//==============================================================================
bool Guiplugin2AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* Guiplugin2AudioProcessor::createEditor()
{
    return new Guiplugin2AudioProcessorEditor (*this);
}

//==============================================================================
void Guiplugin2AudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Guiplugin2AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Guiplugin2AudioProcessor();
}

void Guiplugin2AudioProcessor::updateAngleDelta()
{
    auto cyclesPerSample = *pitch / currentSampleRate;
    angleDelta = cyclesPerSample * 2.0 * MathConstants<double>::pi;
}

AudioThumbnail* Guiplugin2AudioProcessor::getThumbnail()
{
    return &thumbnail;
}
